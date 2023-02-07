const express = require('express')
const app = express()

const { MongoClient, ObjectId} = require('mongodb');
require('dotenv/config');
const client =  new MongoClient(process.env.DB_CONNECTION);

const ServerError = function(msg) {
    return {type: "server", msg: msg}
}

const months = [
    "January", "February",
    "March", "April", "May",
    "June", "July", "August",
    "September", "October",
    "November", "December"
    ];

const approved = ['title', 'director', 'cast', 'country', 'release_year', 'rating', 'duration', 'listed_in', 'description']
const necessities = ['title', 'director', 'duration', 'release_year']
const typeChecks = function(req) {
    return Object.keys(req).every(k => {
        let t
        switch(k){
            case 'title':
                t = typeof(req[k]) === 'string' && req[k].length > 0
                console.log(`${k}: ${t}`)
                return t
                break
            case 'rating':
            case 'description':
                t = typeof(req[k]) === 'string' && req[k].length >= 0
                console.log(`${k}: ${t}`)
                return t
                break
            case 'director':
                t = req[k].length > 0 && req[k].every(e => typeof(e) === 'string' && e.length > 0)
                console.log(`${k}: ${t}`)
                return t
                break
            case 'cast':
            case 'country':
            case 'listed_in':
                t = req[k].every(e => typeof(e) === 'string' && e.length > 0)
                console.log(`${k}: ${t}`)
                return t
                break
            case 'release_year':
                let date = new Date()
                t = typeof(req[k]) === 'number' && req[k] <= date.getFullYear()
                console.log(`${k}: ${t}`)
                return t
                break
            case 'duration':
                t = typeof(req[k]) === 'number' && req[k] >= 0
                console.log(`${k}: ${t}`)
                return t
                break
            default:
                console.log(`Default: ${false}`)
                false
        }
    })
}

function suggestionChecks(filters) {
    if (Object.keys(filters).length === 0) 
        return false

        return Object.keys(filters).every(k => {
        let t
        switch(k) {
            case 'title':
            case 'description':
                t = typeof(filters[k]) === 'string' && filters[k].length > 0 
                break
            case 'director':
            case 'cast':
            case 'listed_in':
                t = filters[k].length > 0 && filters[k].every(e => typeof(e) === 'string' && e.length > 0)
                break
            default:
                t = false 
        }
        return t
    })
} 

function escapeRegExp(text) {
    return text.replace(/[-[\]{}()*+?.,\\^$|#\s]/g, '\\$&');
  }

function generateSearch(filters) {
    let search = {type: 'Movie'}
    search.$and = []
    Object.keys(filters).forEach(k => {
        switch(k) {
            case 'title':
            case 'description':
                search[k] = {$regex: escapeRegExp(filters[k]), $options: 'i'}
                break
            case 'director':
            case 'cast':
            case 'listed_in':
                potentials = []
                filters[k].forEach(el => {
                    obj = {}
                    obj[k] = {$regex: escapeRegExp(el), $options: 'i'}
                    potentials.push(obj)
                })
                search.$and.push({$or: potentials})
                break
            default:
                //throw error
                break
        }
    })
    return search
}

const expandElement = function(key) {
    switch(key) {
        case 'rating':
        case 'description': 
        case 'country':
        case 'listed_in':
        case 'cast': 
            return ""
        default:
            throw ServerError(`expandElement() key '${key}' not defined`)
    }
} 
const prepareElement = function(key, req) {
    switch(key) {
        case 'title':
        case 'description': 
        case 'rating': 
        case 'release_year':
            return req[key]
        case 'director':
        case 'cast':
        case 'country': 
        case 'listed_in':
            if (req[key].length === 0)
                return ""
            else
                return req[key].reduce((acc, el, i) => {return acc += i === 0 ? el : `, ${el}`})
        case 'duration':
            return `${req[key]} min`
        default:
            throw ServerError(`prepareElement() key '${key}' not defined`)
    }
}

app.use(express.json())

const bodyParser=require('body-parser');
app.use(bodyParser.urlencoded({extended: false}))
app.use(bodyParser.json());

async function establishConnection() {
    await client.connect()
    const db = await client.db('NetflixTitles')
    return await db.collection('netflix_titles')
}


function testCreate(req) {
    const keys = Object.keys(req)
    console.log(keys)
    return keys.every(k => approved.includes(k)) && necessities.every(n => keys.includes(n)) && typeChecks(req)
}

app.post('/movie/create', async(req,res)=>{
    const movie = req.body;
    if (testCreate(movie)) {
        try {
            let newMovie = {}
            approved.forEach(key => { newMovie[key] = movie[key] !== undefined ? prepareElement(key, movie) : expandElement(key)})
            let date = new Date()
            newMovie["type"] = "Movie"
            newMovie["date_added"] = `${months[date.getMonth()]} ${date.getDate()}, ${date.getFullYear()}`
            console.log('Movie to create')
            console.log(newMovie)
            const collection = await establishConnection()
            const f = await collection.insertOne(newMovie)
            res.status(201).json({_id: f.insertedId})
        } catch(err) {
            console.log(err.msg)
            res.sendStatus(500)
        }
    }
    else 
        res.sendStatus(400)
})

app.get('/movie', async(req,res)=> {
    const id = req.query["_id"]
    if (id === undefined || typeof(id) !== 'string' || id.length != 24) {
        res.sendStatus(400)
    } else {
        const collection = await establishConnection()
        const f = await collection.findOne({_id: new ObjectId(id)})
        console.log(f)
        if (!f)
            res.sendStatus(204)
        else
            res.status(200).json(f)
    }
})

app.delete('/movie', async(req,res)=> {
    const id = req.body["_id"]
    if (id === undefined || typeof(id) !== 'string') {
        res.sendStatus(400)
    } else {
        const collection = await establishConnection()
        await collection.deleteOne({_id: new ObjectId(id)})
        res.sendStatus(200)
    }
})

app.put('/movie/update', async(req,res)=> {
    const id = req.body["_id"]
    let updates = req.body
    delete updates._id
    const keys = Object.keys(updates)

    if (id && keys.every(k => approved.includes(k)) && typeChecks(updates)) {
        try {
            movieUpdates = {}
            keys.forEach(key => {
                    movieUpdates[key] = prepareElement(key, updates)
                })
    
            const collection = await establishConnection()
            console.log(keys)
            console.log(movieUpdates)
            const f = await collection.findOneAndUpdate({_id:new ObjectId(id)}, {$set: movieUpdates})
            console.log(f)
            
            res.sendStatus(200)
        } catch(err) {
            console.log(err.msg)
            res.sendStatus(500)
        }
    } else 
        res.sendStatus(400)
})

app.post('/movie/suggestions',async(req,res)=>{
    const filters = req.body;
    if(!suggestionChecks(filters)) {
        await res.sendStatus(400)
    }

    const search = generateSearch(filters)
    const collection = await establishConnection()
    console.log('filters:')
    console.log(filters);
    console.log("search")
    console.log(JSON.stringify(search, null, 4));
    // console.log(search);
    const result = await collection.find(search).toArray();

    await res.json(result);
})

app.listen(3000)
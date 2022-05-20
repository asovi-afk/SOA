const express = require('express');
const router=express.Router();

const bodyParser=require('body-parser');
router.use(bodyParser.urlencoded({extended: false}))
router.use(bodyParser.json());

const { MongoClient } = require('mongodb');
const req = require('express/lib/request');
const res = require('express/lib/response');
require('dotenv/config');
const client =  new MongoClient(process.env.DB_CONNECTION);


router.get('/getall',async(req,res)=>{
    
    await client.connect();
    const  database = await client.db('SOA');
    const collection = await database.collection('Alergeni');
    const result = await collection.find().toArray();

    await res.json(result);
    
});

router.get("/get-alergen-of-specific-type", async (req,res)=>{

        await client.connect();
        const  database = await client.db('SOA');
    
        const collectionAlergeni = await database.collection('Alergeni');
        const collectionTipoviAlergena = await database.collection('TipoviAlergena');
    
        findTipAlergena = await collectionTipoviAlergena.findOne({name: req.body.name});
        findAlergeni = await collectionAlergeni.find().toArray();
    
        let array = [];
        await findAlergeni.forEach(result => {
            if(result.allergenicity==findTipAlergena.id)
            {
                 array.push(result);
            }
        });
    
        await res.json(array);
    
});

router.get('/insertall',async(req,res)=>{

    await client.connect();
    const  database = await client.db('SOA');
    const collection = await database.collection('Alergeni');

    let docs=[{"id":1,"name":"ACER","localized_name":"ЈАВОР","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":1,"allergenicity_display":"mild"},{"id":2,"name":"ALNUS","localized_name":"ЈОВА","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":3,"allergenicity_display":"high"},{"id":3,"name":"AMBROSIA","localized_name":"АМБРОЗИЈА","margine_top":100,"margine_bottom":30,"type":3,"allergenicity":3,"allergenicity_display":"high"},{"id":4,"name":"ARTEMISIA","localized_name":"ПЕЛИН","margine_top":100,"margine_bottom":60,"type":3,"allergenicity":3,"allergenicity_display":"high"},
    {"id":5,"name":"BETULA","localized_name":"БРЕЗА","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":3,"allergenicity_display":"high"},{"id":6,"name":"CANNABACEAE","localized_name":"КОНОПЉЕ","margine_top":100,"margine_bottom":60,"type":3,"allergenicity":1,"allergenicity_display":"mild"},{"id":7,"name":"CARPINUS","localized_name":"ГРАБ","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":1,"allergenicity_display":"mild"},
    {"id":26,"name":"CELTIS","localized_name":"КОПРИВИЋ","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":1,"allergenicity_display":"mild"},{"id":8,"name":"CHENOP/AMAR.","localized_name":"ШТИРЕВИ/ПЕПЕЉУГЕ","margine_top":100,"margine_bottom":60,"type":3,"allergenicity":2,"allergenicity_display":"moderate"},
    {"id":9,"name":"CORYLUS","localized_name":"ЛЕСКА","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":2,"allergenicity_display":"moderate"},{"id":10,"name":"CUPRESS/TAXA.","localized_name":"ТИСА/ЧЕМПР.","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":2,"allergenicity_display":"moderate"},{"id":11,"name":"FAGUS","localized_name":"БУКВА","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":1,"allergenicity_display":"mild"},{"id":12,"name":"FRAXINUS","localized_name":"ЈАСЕН","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":2,"allergenicity_display":"moderate"},{"id":13,"name":"JUGLANS","localized_name":"ОРАХ","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":2,"allergenicity_display":"moderate"},{"id":14,"name":"MORACEAE","localized_name":"ДУД","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":1,"allergenicity_display":"mild"},
    {"id":15,"name":"PINACEAE","localized_name":"ЧЕТИНАРИ","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":1,"allergenicity_display":"mild"},{"id":16,"name":"PLANTAGO","localized_name":"БОКВИЦА","margine_top":100,"margine_bottom":60,"type":3,"allergenicity":2,"allergenicity_display":"moderate"},{"id":17,"name":"PLATANUS","localized_name":"ПЛАТАН","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":2,"allergenicity_display":"moderate"},{"id":18,"name":"POACEAE","localized_name":"ТРАВЕ","margine_top":100,"margine_bottom":60,"type":2,"allergenicity":3,"allergenicity_display":"high"},
    {"id":19,"name":"POPULUS","localized_name":"ТОПОЛА","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":2,"allergenicity_display":"moderate"},{"id":20,"name":"QUERCUS","localized_name":"ХРАСТ","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":2,"allergenicity_display":"moderate"},{"id":21,"name":"RUMEX","localized_name":"КИСЕЛИЦЕ","margine_top":100,"margine_bottom":60,"type":3,"allergenicity":2,"allergenicity_display":"moderate"},{"id":22,"name":"SALIX","localized_name":"ВРБА","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":1,"allergenicity_display":"mild"},{"id":23,"name":"TILIA","localized_name":"ЛИПА","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":1,"allergenicity_display":"mild"},{"id":24,"name":"ULMACEAE","localized_name":"БРЕСТ","margine_top":100,"margine_bottom":60,"type":1,"allergenicity":1,"allergenicity_display":"mild"},{"id":25,"name":"URTICACEAE","localized_name":"КОПРИВА","margine_top":100,"margine_bottom":60,"type":3,"allergenicity":3,"allergenicity_display":"high"}];

    const result= await collection.insertMany(docs); 

    await res.json(result);

});



module.exports=router;
const express = require('express');
const router=express.Router();

const { MongoClient } = require('mongodb');
require('dotenv/config');
const client =  new MongoClient(process.env.DB_CONNECTION);


router.get('/getall',async(req,res)=>{
    
    await client.connect();
    const  database = await client.db('SOA');
    const collection = await database.collection('Lokacije');
    const result = await collection.find().toArray();

    await res.json(result);
    
});

router.get('/insertall',async(req,res)=>{

    await client.connect();
    const  database = await client.db('SOA');
    const collection = await database.collection('Lokacije');

    let docs=[{"id":2,"name":"БЕОГРАД - ЗЕЛЕНО БРДО","latitude":"44.786241","longitude":"20.521657","description":"Zgrada Agencije"},
    {"id":1,"name":"БЕОГРАД - НОВИ БЕОГРАД","latitude":"44.823174","longitude":"20.412914","description":"Zgrada Opsine"},
    {"id":17,"name":"БЕЧЕЈ","latitude":"45.613056","longitude":"20.052766","description":"Zgrada sportskog centra Mladost"},
    {"id":27,"name":"ВАЉЕВО","latitude":"44.270884","longitude":"19.887231","description":"Zgrada Opstine"},
    {"id":8,"name":"ВРАЊЕ","latitude":"42.551460","longitude":"21.902314","description":"Zgrada Zavoda"},{"id":25,"name":"ВРБАС","latitude":"45.572060","longitude":"19.640300","description":"Zgrada Skupštine opštine"},{"id":9,"name":"ВРШАЦ","latitude":"45.116670","longitude":"21.303610","description":""},{"id":10,"name":"ЗАЈЕЧАР","latitude":"43.906308","longitude":"22.278354","description":"Jugoistok-ogranak ED Zajecar"},{"id":16,"name":"ЗЛАТИБОР","latitude":"43.721861","longitude":"19.708328","description":"Auto kamp"},{"id":26,"name":"ЗРЕЊАНИН","latitude":"45.382230","longitude":"20.395474","description":"Institut za javno zdravlje"},{"id":22,"name":"КИКИНДА","latitude":"45.832550","longitude":"20.478461","description":"Zgrada Opšte bolnice"},{"id":4,"name":"КРАГУЈЕВАЦ","latitude":"44.011812","longitude":"20.915890","description":"Zgrada Instituta"},{"id":12,"name":"КРАЉЕВО","latitude":"43.723994","longitude":"20.688908","description":"JKP Putevi"},{"id":5,"name":"КРУШЕВАЦ","latitude":"43.581566","longitude":"21.320344","description":"Zgrada Zavoda"},{"id":6,"name":"КУЛА","latitude":"45.701588","longitude":"19.381502","description":"Dom kulture"},{"id":14,"name":"ЛОЗНИЦА","latitude":"44.537135","longitude":"19.229862","description":"Zdravstveni centar Dr Milenko Marin"},{"id":15,"name":"НИШ","latitude":"43.316286","longitude":"21.913684","description":"Institut za javno zdravlje"},{"id":20,"name":"НОВИ ПАЗАР","latitude":"43.140807","longitude":"20.518374","description":"Zgrada gradske uprave"},{"id":21,"name":"ОБРЕНОВАЦ","latitude":"44.658181","longitude":"20.200040","description":"JP za zastitu zivotne sredine"},{"id":11,"name":"ПАНЧЕВО","latitude":"44.870078","longitude":"20.640069","description":"Gradska uprava grada Pančevo"},{"id":7,"name":"ПОЖАРЕВАЦ","latitude":"44.621157","longitude":"21.189076","description":"Zgrada Zavoda"},{"id":19,"name":"СОКОБАЊА","latitude":"43.639534","longitude":"21.868399","description":"Bolnica za plucne bolesti"},{"id":24,"name":"СОМБОР","latitude":"45.779140","longitude":"19.110500","description":"Institut za javno zdravlje"},{"id":23,"name":"СРЕМСКА МИТРОВИЦА","latitude":"44.971610","longitude":"19.612680","description":"Zgrada osnovnog Suda"},{"id":13,"name":"СУБОТИЦА","latitude":"46.104969","longitude":"19.668574","description":"Zgrada Zavoda"},
    {"id":3,"name":"ЧАЧАК","latitude":"43.892702","longitude":"20.344355","description":"Zavod za javno zdravlje"}];

    const result= await collection.insertMany(docs); 

    await res.json(result);

});




module.exports=router;
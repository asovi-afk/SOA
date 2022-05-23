const express = require('express');

const port = process.env.PORT || 5000;

const app = express();

const bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json())

const axios = require('axios');


app.post('/',async (req,res)=>{

   const response = await axios.post("http://10.7.99.95:8080/function/translate-async", req.body.input); 
   await res.json(response.data);

});

app.get('/',(req,res)=>{
    
    res.sendFile('client.html', {root: __dirname})
});



app.listen(port,()=>{
    console.log(`App is listening to port  ${port}`);
});
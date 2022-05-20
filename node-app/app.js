const express = require('express');

const app = express();
const port = process.env.PORT || 5000;

/*const swaggerJsDoc=require('swagger-jsdoc');
const swaggerUi=require('swagger-ui-express');

const swaggerOptions={
    swaggerDefinition:{
        info: {
            title: 'SOA API',
            description:'Dokumentacija za API',
            servers: ['http://localhost:5000']
        }
    },
    apis:['app.js']
};*/

//const swaggerDocs = swaggerJsDoc(swaggerOptions);
//app.use('/api-docs',swaggerUi.serve,swaggerUi.setup(swaggerDocs));



const routesAlergeni=require('./routes/Alergeni');
const routesKoncentracije=require('./routes/Koncentracije');
const routePolen=require('./routes/Polen');
const routerLokacije=require('./routes/Lokacije');
const routerTipoviAlergena=require('./routes/TipoviAlergena');


app.use('/tipovialergena',routerTipoviAlergena);
app.use('/lokacije',routerLokacije);
app.use('/polen',routePolen);
app.use('/alergeni',routesAlergeni);
app.use('/koncentracije',routesKoncentracije);


app.get('/',(req,res)=>{
    res.send(`App is listening to port  ${port}`);
});

app.listen(port,()=>{
    console.log(`App is listening to port  ${port}`);
});
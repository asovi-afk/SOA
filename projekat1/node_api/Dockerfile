FROM node:18.12-alpine3.15
WORKDIR /api

COPY ./development/app.js .

RUN ["npm", "init", "-y"]
RUN ["npm", "install", "dotenv", "--save"]
RUN ["npm", "install", "express", "--save"]
RUN ["npm", "install", "mongodb"]

ENTRYPOINT [ "node" , "./app.js" ]
CMD []


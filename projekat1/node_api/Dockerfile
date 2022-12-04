FROM node:18.12-alpine3.15
WORKDIR /api

COPY ./development/app.js .
COPY ./development/package*.json ./
RUN ["ls", "-l"]
RUN ["npm", "install"]
ENTRYPOINT [ "node" , "./app.js" ]
CMD []

# RUN ["npm", "init", "-y"]
# RUN ["npm", "install", "dotenv", "--save"]
# RUN ["npm", "install", "express", "--save"]
# RUN ["npm", "install", "mongodb"]

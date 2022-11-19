//const http = require('http');
const child = require('child_process');
const express = require('express');
const cors = require('cors');

const app = express();
app.use(cors());

/*
http.createServer((req, res) => {
    console.log(req.headers);
    const command = req.headers.command;
    if(command){
        const commandString = `doas /home/igor/2022.1/ihs/projeto/t ${command}`;
        child.exec(commandString);
    }
    res.end();
}).listen(5000);
*/

app.get('/', (req, res) => {
    const h = req.headers;
    console.log(h);
    const command = h.command;
    if(command){
        const commandString = `doas ../t ${command}`;
        child.exec(commandString);
    }
    res.send();
});

app.listen(5000, _ => console.log('listening'));

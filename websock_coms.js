const { reverse } = require('dns');
const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);

// Websocket part
const { Server } = require("socket.io");
const io = new Server(server);

// creates a custom html server
app.get('/', (req, res)=>{
    res.sendFile(__dirname + '/web_sock.html');

});

var received_msg;

// handling on websocket server connection
io.on('connection', (socket)=>{
    console.log("A client has connected");

    socket.on('sampleEvent', (msg)=>{
        console.log('message: ' + msg);
        io.emit('sampleEvent', "I am a dick");
    });

    socket.on('cppEvent', (msg)=>{
        console.log('cpp message: ' + msg);
        io.emit('cppEvent', 'Message received');
    });

    socket.on('sampleEvent2', (msg)=>{
        console.log(received_msg + " and " + msg);
    
        io.emit('sampleEvent2', received_msg);
    });

    
    socket.on('disconnect', ()=>{
        console.log("The client has disconnected");
    });
});



//create the necessary PORT to send the html content too
const PORT = 3000;
server.listen(PORT, () => {
    console.log("Listening to port: " + PORT);
});
const net = require('net');

const HOST = '127.0.0.1';
const PORT = 65432;

const server = net.createServer((socket) => {
    console.log(`Connected to ${socket.remoteAddress}:${socket.remotePort}`);
    
    socket.on('data', (data) => {
        console.log(`Received: ${data.toString()}`);
        socket.write('Message received!');
    });

    socket.on('end', () => {
        console.log('Client disconnected');
    });

    socket.on('error', (err) => {
        console.error('Socket error:', err);
    });
});

server.listen(PORT, HOST, () => {
    console.log(`Server listening on ${HOST}:${PORT}`);
});

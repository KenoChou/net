const net = require('net');

const HOST = '127.0.0.1';
const PORT = 65432;

const client = new net.Socket();

client.connect(PORT, HOST, () => {
    console.log(`Connected to server at ${HOST}:${PORT}`);
    client.write('Hello, Server!');
});

client.on('data', (data) => {
    console.log(`Received from server: ${data.toString()}`);
    client.destroy(); // Close the connection after receiving data
});

client.on('close', () => {
    console.log('Connection closed');
});

client.on('error', (err) => {
    console.error('Socket error:', err);
});

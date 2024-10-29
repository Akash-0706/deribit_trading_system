// app.js

const apiUrl = "http://localhost:8080"; // Replace with your actual backend URL
const wsUrl = "ws://localhost:9002"; // Replace with your WebSocket server URL

function placeOrder(instrument, type, amount, price) {
    fetch(`${apiUrl}/api/v2/private/${type}`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': `Bearer YOUR_ACCESS_TOKEN`
        },
        body: JSON.stringify({ instrument_name: instrument, amount, price, type })
    })
    .then(response => response.json())
    .then(data => console.log("Order placed:", data))
    .catch(error => console.error("Order error:", error));
}

function initializeWebSocket() {
    const ws = new WebSocket(wsUrl);
    ws.onopen = () => console.log("Connected to WebSocket");
    ws.onmessage = event => {
        const data = JSON.parse(event.data);
        document.getElementById("order-book").innerHTML = JSON.stringify(data);
    };
    ws.onclose = () => console.log("WebSocket closed");
}

document.getElementById("order-form").addEventListener("submit", event => {
    event.preventDefault();
    const instrument = document.getElementById("instrument").value;
    const type = document.getElementById("type").value;
    const amount = parseFloat(document.getElementById("amount").value);
    const price = parseFloat(document.getElementById("price").value);
    placeOrder(instrument, type, amount, price);
});

window.onload = initializeWebSocket;

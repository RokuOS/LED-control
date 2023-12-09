const express = require("express");
const app = express();
const http = require("http");
const WebSocket = require("ws");
const path = require("path");
const port = 3000;

const server = http.createServer(app);
const ws = new WebSocket.Server({ server });

//Chạy server trên cổng 3000
server.listen(port, () => {
  console.log("Server is running on port " + port);
});

//Danh sách client
var clients = [];

//Client kết nối đến server
ws.on("connection", function (socket, req) {
  //Thêm socket_id vào danh sách clients
  clients.push(socket);
  console.log("Connected");
  const url = req.url;

  //Nếu đường dẫn là Esp8266
  if (url === "/esp8266") {
    console.log("ESP8266 connected");

    //Lắng nghe sự kiện gửi từ client Esp8266 về server
    socket.on("message", function (message) {
      console.log(String(message));
    });
  }
  //Nếu đường dẫn là Web
  else if (url === "/web-client") {
    //Lắng nghe sự kiện gửi từ client Web về server
    socket.on("message", function (message) {
      console.log("received: %s", JSON.parse(message));

      //Chuyển một Json thành đối tượng trong javascript
      const data = JSON.parse(message);

      broadcast(JSON.stringify(data), socket);

      console.log("Số lượng client connect: " + clients.length + 1);
    });
  }
  socket.on("close", function () {
    console.log("Disconnected");
  });
});

//Hàm gửi dữ liệu đến các clients khác
function broadcast(data, sender) {
  clients.forEach((client) => {
    if (client !== sender && client.readyState === WebSocket.OPEN) {
      client.send(data);
    }
  });
}

app.get("/", (req, res) => res.sendFile(path.join(__dirname, "/index.html")));

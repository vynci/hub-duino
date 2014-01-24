
/**
 * Module dependencies.
 */

var express = require('express');
var routes = require('./routes');
var user = require('./routes/user');
var http = require('http');
var path = require('path');
var serialport = require("serialport").SerialPort;

var portName = '/dev/tty.Bluetooth-Modem'; //This is the standard Raspberry Pi Serial port
 
var readData = ''; //Array to hold the values read in from the port
var sendData = "0";
var sendData1 = "0";
var sendData2 = "0";
var sendDataTemp = "27";
var cnt = 0;
 
var sp = new serialport(portName, {
  baudRate: 9600,
  dataBits: 8,
  parity: 'none',
  stopBits: 1,
  flowControl: false
});

var app = express();
 
app.configure(function(){
  app.set('port', process.env.PORT || 3000);
  app.set('views', __dirname + '/views');
  app.set('view engine', 'jade');
  app.use(express.favicon());
  app.use(express.logger('dev'));
  app.use(express.bodyParser());
  app.use(express.methodOverride());
  app.use(app.router);
  app.use(express.static(path.join(__dirname, 'public')));
});
 
app.configure('development', function(){
  app.use(express.errorHandler());
});
 
app.get('/', routes.index);
app.get('/users', user.list);
 
/**
 * Actual Server Code
 */

var server = http.createServer(app).listen(app.get('port'), function(){
  console.log("Express server listening on port " + app.get('port'));
});

app.get('/', function(req, res) {
  res.json(quotes);
});
 
var io = require('socket.io').listen(server);
 
  /**
 * Server and socket started, below are all my listeners and emitters
 */
 
io.sockets.on('connection', function(socket){
  console.log("Socket connected"); 
  socket.emit('connected', 123);

  socket.on('sendSerial', function(data) {
  console.log(data); 
	   sp.write(data);
  });
 
  sp.on('close', function (err) {
    console.log('port closed');
  });
 
  sp.on('error', function (err) {
    console.error("error", err);
  });
 
  sp.on('open', function () {
    console.log('port opened...');
  });
});
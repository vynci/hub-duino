/**
 * Module dependencies.
 */

var express = require('express');
var routes = require('./routes');
var user = require('./routes/user');
var http = require('http');
var path = require('path');
var serialport = require("serialport").SerialPort;
var github = require('octonode');
var say = require('say');

var client = github.client({
    username: 'vynci',
    password: 'xxx'
});

var portName = '/dev/tty.usbmodem1421'; 

var cnt = 0;
var cnt1 = 0;
var notifcationFlag = 0;
var tmp;

var sp = new serialport(portName, {
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false
});

var app = express();

app.configure(function() {
    app.set('port', process.env.PORT || 7000);
    app.set('views', __dirname + '/views');
    app.set('view engine', 'jade');
    app.use(express.favicon());
    app.use(express.logger('dev'));
    app.use(express.bodyParser());
    app.use(express.methodOverride());
    app.use(app.router);
    app.use(express.static(path.join(__dirname, 'public')));
});

app.configure('development', function() {
    app.use(express.errorHandler());
});

app.get('/', routes.index);
app.get('/users', user.list);

/**
 * Actual Server Code
 */

var server = http.createServer(app).listen(app.get('port'), function() {
    console.log("Express server listening on port " + app.get('port'));
});

var io = require('socket.io').listen(server);

/**
 * Server and socket started, below are all my listeners and emitters
 */



// client.limit(function(err, left, max) {
//     console.log(left);
//     console.log(max);
// });

setInterval(function() {
    //client.get('/repos/School-Improvement-Network/platform/pulls', {}, function(err, status, body, headers) {
    client.get('/repos/School-Improvement-Network/backbone.content-navigation/pulls', {}, function(err, status, body, headers) {    
        console.log(body); //json object
        if (body.length > 0) {
            sp.write('d');
            console.log("Pull!");
            cnt1 = 0;
            sp.write('a');

            if (cnt < 2) {
                sp.write('0');
                notifcationFlag = 1;                               
            }
            if(cnt < 1){
                if(body[0].user.login === 'maodes'){
                    body[0].user.login = 'mao-des';
                }
                if(body[0].user.login === 'vjcagay'){
                    body[0].user.login = 'vj kaggay';
                }
                if(body[0].user.login === 'ronald-gemao07'){
                    body[0].user.login = 'ronald gih mao';
                }
                if(body[0].user.login === 'vynci'){
                    body[0].user.login = 'vinci';
                }                 
                say.speak('Vicki', 'Pull request by, ' + body[0].user.login);
                tmp = body[0].user.login;
            }
            cnt++;
        } 
        else if(body.length == undefined){
            console.log("beep boop!");
        }
        else {
            console.log("Empty");            
            sp.write('b');
            cnt = 0;
            if (notifcationFlag == 1) {
                sp.write('1');
                notifcationFlag = 0;
                say.speak('Vicki', tmp + ', Pull request closed!');
            }
            if (cnt1 < 5) {
                sp.write('c');
            } else {
                sp.write('d');
            }
            cnt1++;

        }
    });

}, 9000);

io.sockets.on('connection', function(socket) {
    console.log("Socket connected");
    socket.emit('connected', 123);

    socket.on('sendSerial', function(data) {
        console.log(data);
        sp.write(data);
    });

    sp.on('close', function(err) {
        console.log('port closed');
    });

    sp.on('error', function(err) {
        console.error("error", err);
    });

    sp.on('open', function() {
        console.log('port opened...');
    });
});
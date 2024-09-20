const maxValue = 50 ;
const minValue = -50 ;
const sendInterval = 100 ; // 每500毫秒發送一次請求

const totalSize = 200 ;
const joyRadius = 40 ;
const joystickRadius = totalSize / 2 ;
const maxDistance  = joystickRadius - joyRadius ;
let lastSendTime = 0 ;

const colors = {
    'r' : [255, 0, 0],
    'y' : [255, 255, 0],
    'g' : [0, 255, 0],
    'b' : [0, 0, 255],
    'n' : [0, 0, 0]
} ;

const tail_angles = {
    'r' : 1638,
    'm' : 7373,
    'l' : 9285
} ;

const head_angles = {
    'r' : [9285, 1638],
    'm' : [9285, 6735],
    'l' : [9285, 8009],
    'n' : [1638, 6735]
} ;

function init() {

    const stage = new createjs.Stage('joystick') ;
    const psp = new createjs.Shape() ;
    let xCenter = joystickRadius ;
    let yCenter = joystickRadius ;
    
    psp.graphics.beginFill('#ffa78f').drawCircle(xCenter, yCenter, joyRadius) ;
    psp.alpha = 0.3 ;
    stage.addChild(psp) ;

    stage.canvas.width = totalSize;
    stage.canvas.height = totalSize;
    
    createjs.Ticker.framerate = 60 ;
    createjs.Ticker.addEventListener('tick', () => stage.update()) ;

    const myElement = $('#joystick')[0] ;
    const mc = new Hammer(myElement) ;

    mc.on("panstart", () => {
        xCenter = psp.x ;
        yCenter = psp.y ;
        psp.alpha = 0.5 ;
        stage.update() ;
    });

    mc.on("panmove", (ev) => {
        const { x, y } = calculateCoords(ev.angle, ev.distance) ;
        psp.x = x ;
        psp.y = y ;

        const l =  map(clamp(x + (-1 * y)), maxValue, 255) ;
        const r = map(clamp((-1 * x) + (-1 * y)), maxValue, 255) ;

        $('#Left-value').text(Math.round(l)) ;
        $('#Right-value').text(Math.round(r)) ; // set txt

        sendMotorValues(l, r) ;
    });

    mc.on("panend", () => {
        $('#Right-value').text('0') ;
        $('#Left-value').text('0') ;

        const xhttp = new XMLHttpRequest() ;
        xhttp.open("GET", `/motor?duty=0,0`, true) ;
        xhttp.send();

        psp.alpha = 0.3;
        createjs.Tween.get(psp).to({ x: xCenter, y: yCenter }, 750, createjs.Ease.elasticOut) ;
    }) ;
}

function calculateCoords(angle, distance) {

    let rads = (angle * Math.PI) / 180.0;
    distance = Math.min(distance, maxDistance) ;

    return {
        x: distance * Math.cos(rads),
        y: distance * Math.sin(rads)
    };
}

function clamp(value) {
  return Math.max(minValue, Math.min(maxValue, value)) ;
}

function map(value, origin, reflect){
    return Math.round(value * reflect / origin)
}

function sendMotorValues(l, r) {
  var currentTime = new Date().getTime() ;

  if (currentTime - lastSendTime >= sendInterval) {
    
    lastSendTime = currentTime ;

    const xhttp = new XMLHttpRequest() ;
    xhttp.open("GET", `/motor?duty=${l},${r}`, true) ;
    xhttp.send() ;
  }
}

function color(color_arg) {
  var xhttp = new XMLHttpRequest() ;
  xhttp.open("GET", `/led?duty=${colors[color_arg][0]},${colors[color_arg][1]},${colors[color_arg][2]}`, true) ;
  xhttp.send() ;
}

function tail(angle_arg) {
  var xhttp = new XMLHttpRequest() ;
  xhttp.open("GET", `/tail?duty=${tail_angles[angle_arg]}`, true) ;
  xhttp.send() ;
}

function f_head(angle_arg) {
  var xhttp = new XMLHttpRequest() ;
  xhttp.open("GET", `/head?duty=${head_angles[angle_arg][0]},${head_angles[angle_arg][1]}`, true) ;
  xhttp.send() ;
}

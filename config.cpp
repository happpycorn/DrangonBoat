#include "config.h"

const char* indexHtml = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="https://code.createjs.com/1.0.0/createjs.min.js"></script>
    <script src="https://hammerjs.github.io/dist/hammer.min.js"></script>
    <title>Drongan Boat Controlor | Fhehs</title>
    <style>
        html{
            box-sizing: border-box;
            height: 100%;
            overflow: hidden;
            touch-action: none;
            user-select: none;
            -webkit-user-select: none;
            -moz-user-select: none;
            -ms-user-select: none;
        }

        *,
        *::before,
        *::after{
            box-sizing: inherit;
            margin: 0;
            padding: 0;
        }

        body{
            align-items: center;
            background: linear-gradient(45deg, #ffa78f, #ffd3df);
            display: flex;
            font-family: 'Dosis', sans-serif;
            font-display: swap;
            height: inherit;
            justify-content: center;
        }

        .wrapper{
            
            flex-basis: 95%;
            height: 95%;
            padding: 20px 35px;

            backdrop-filter: blur(5.5px);
            -webkit-backdrop-filter: blur(5.5px);
            background: rgba(255, 255, 255, 0.75);
            border: 1px solid rgba(255, 255, 255, 0.01);
            border-radius: 16px;
            box-shadow: 0 4px 30px rgba(35, 35, 35, 0.1);
            color: #232323;
            backdrop-filter: blur(4px);
            -webkit-backdrop-filter: blur(4px);
            background: rgba(255, 255, 255, 0.30);
        }

        .view-bar{
            font-size: 15px;
            padding: 20px;

            backdrop-filter: blur(5.5px);
            -webkit-backdrop-filter: blur(5.5px);
            background: rgba(255, 255, 255, 0.5);
            border: 1px solid rgba(255, 255, 255, 0.01);
            border-radius: 16px;
            box-shadow: 0 4px 30px rgba(35, 35, 35, 0.1);
            color: #232323;
            overflow: auto;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }

        span{
            font-size: 15px;
            padding: 10px;
        }

        button{
            width: 40px;
            height: 40px;
            padding: 10px;
            font-size: 15px;
            margin: 2px;

            backdrop-filter: blur(5.5px);
            -webkit-backdrop-filter: blur(5.5px);
            background: rgba(255, 255, 255, 0.75);
            border: 1px solid rgba(255, 255, 255, 0.01);
            border-radius: 10px;
            box-shadow: 0 4px 30px rgba(35, 35, 35, 0.1);
            overflow: auto;
        }

        button:hover{
            background-color: inherit;
            color: inherit;
        }

        #joystick {
            border-radius: 50%;
            width: 200px;
            height: 200px;

            backdrop-filter: blur(5.5px);
            -webkit-backdrop-filter: blur(5.5px);
            background: rgba(255, 255, 255, 0.75);
            border: 1px solid rgba(255, 255, 255, 0.01);
            box-shadow: 0 4px 30px rgba(35, 35, 35, 0.1);

            position: absolute;
            bottom: 0;
            left: 0;
            margin: 20px;
        }

        #head-frame{
            position: absolute;
            bottom: 0;
            right: 0;
            padding: 10px;
        }

        .head{
            height: 200px;
            width: 100px;
            margin: 10px;
        }
    </style>
</head>
<body onload="init();">

    <div class="wrapper">
        <!-- View Bar -->
        <section class="view-bar">
            <div class="bar value">
                <span id="Left-value">0</span>
                <span id="Right-value">0</span>
            </div>
            <div class="bar color">
                <span>LED</span>
                <button class="color" onclick="color('r')">R</button>
                <button class="color" onclick="color('y')">Y</button>
                <button class="color" onclick="color('g')">G</button>
                <button class="color" onclick="color('b')">B</button>
                <button class="color" onclick="color('n')">N</button>
            </div>
            <div class="bar tail">
                <span>Tail</span>
                <button class="tail" onclick="tail('l')">L</button>
                <button class="tail" onclick="tail('m')">M</button>
                <button class="tail" onclick="tail('r')">R</button>
            </div>
        </section>
        <section class="control">
            <div id="joystick-frame">
                <canvas id="joystick"></canvas>
            </div>
            <div id="head-frame">
                <button class="head" onclick="f_head('l')">L</button>
                <button class="head" onclick="f_head('m')">M</button>
                <button class="head" onclick="f_head('r')">R</button>
            </div>
        </section>
    </div>

    <script>
        const maxValue = 50 ;
        const minValue = -50 ;
        const sendInterval = 100 ; // 每500毫秒發送一次請求

        const totalSize = 200 ;
        const joyRadius = 35 ;
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
            'l' : 180,
            'm' : 90,
            'r' : 0
        } ;

        const head_angles = {
            'l' : [180, 180],
            'm' : [90, 90],
            'r' : [0, 0]
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
    </script>
</body>
</html>
)=====";
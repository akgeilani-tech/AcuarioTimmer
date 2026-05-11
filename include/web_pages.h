#pragma once

const char INDEX_HTML[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">

<title>
Aquarium Controller
</title>

<style>

body{
    font-family:Arial;
    margin:20px;
    background:#f0f0f0;
}

.card{
    background:white;
    padding:20px;
    border-radius:10px;
    margin-bottom:20px;
}

button{
    padding:10px 20px;
}

input{
    display:block;
    margin-bottom:10px;
}
#clock{

    font-size:48px;

    font-weight:bold;

    text-align:center;

    padding:20px;
}

</style>

</head>

<script>

async function loadSchedulerStatus() {

    try {

        const response =
            await fetch(
                '/scheduler'
            );

        const data =
            await response.json();

        document.getElementById(
            'lightsOnStatus'
        ).innerText =
            data.lightsOn;

        document.getElementById(
            'lightsOffStatus'
        ).innerText =
            data.lightsOff;

        document.getElementById(
            'feed1Status'
        ).innerText =
            data.feed1;

        document.getElementById(
            'feed2Status'
        ).innerText =
            data.feed2;
    }
    catch(error) {

        console.log(error);
    }
}

window.onload =
    loadSchedulerStatus;

</script>

<body>

<h1>
Aquarium Controller
</h1>

<div class="card">

<h2>
Current Time
</h2>

<div id="clock">
--:--
</div>

</div>
<div class="card">
    <h2>Scheduler Status</h2>

    <p>
        Lights ON:
        <span id="lightsOnStatus"> -- </span>
    </p>

    <p>
        Lights OFF:
        <span id="lightsOffStatus"> -- </span>
    </p>

    <p>
        Feed Time 1:
        <span id="feed1Status"> -- </span>
    </p>

    <p>
        Feed Time 2:
        <span id="feed2Status"> -- </span>
    </p>

</div>

<div class="card">

<h2>Lights</h2>

<label>ON</label>
<input type="time" lang="en-GB" id="lights_on">

<label>OFF</label>
<input type="time" lang="en-GB" id="lights_off">

</div>

<div class="card">

<h2>Feeding</h2>

<input type="time" lang="en-GB" id="feed1">

<input type="time" lang="en-GB" id="feed2">

</div>

<button onclick="saveConfig()">
Save
</button>

<script>

function saveConfig(){

    const data = {

        lights_on:
            document.getElementById(
                "lights_on"
            ).value,

        lights_off:
            document.getElementById(
                "lights_off"
            ).value,

        feed1:
            document.getElementById(
                "feed1"
            ).value,

        feed2:
            document.getElementById(
                "feed2"
            ).value
    };

    fetch('/save',{

        method:'POST',

        headers:{
            'Content-Type':
            'application/json'
        },

        body:JSON.stringify(data)
    });
    loadSchedulerStatus();
}

async function updateClock(){

    const response =
        await fetch('/time');

    const text =
        await response.text();

    document.getElementById(
        'clock'
    ).innerHTML = text;
}

setInterval(
    updateClock,
    1000
);

updateClock();

</script>

</body>
</html>

)rawliteral";

const char WIFI_SETUP_HTML[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">

<title>
WiFi Setup
</title>

<style>

body{
    font-family:Arial;
    margin:20px;
}

input{
    display:block;
    margin-bottom:10px;
    padding:10px;
    width:300px;
}

button{
    padding:10px 20px;
}

</style>

</head>

<body>

<h1>
WiFi Setup
</h1>

<input
    id="ssid"
    placeholder="WiFi SSID"
>

<input
    id="password"
    type="password"
    placeholder="WiFi Password"
>

<button onclick="saveWifi()">
Save
</button>

<script>

async function saveWifi(){

    const data = {

        ssid:
            document.getElementById(
                "ssid"
            ).value,

        password:
            document.getElementById(
                "password"
            ).value
    };

    await fetch('/savewifi',{

        method:'POST',

        headers:{
            'Content-Type':
            'application/json'
        },

        body:JSON.stringify(data)
    });

    alert(
        "Device restarting..."
    );
}

</script>

</body>
</html>

)rawliteral";
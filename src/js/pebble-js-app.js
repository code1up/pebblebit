
// Rec4EstU
// "ready" event handler.
var ready = function (e) {
    console.log("PebbleBit:ready()");
};

// "showConfiguration" event handler.
var showConfiguration = function () {
    console.log("PebbleBit:showConfiguration()");

    Pebble.openURL("https://pebblebit.azurewebsites.net?pebble=1");
};

var sendPebbleStatusAppMessage = function(status) {
    Pebble.sendAppMessage({
        status: status
    });
}

var sendPebbleErrorAppMessage = function(error) {
    Pebble.sendAppMessage({
        error: error
    });
}

var sendPebbleStepsAppMessage = function(steps) {
    Pebble.sendAppMessage({
        steps: steps
    });
}

var webviewclosed = function (e) {
    console.log("PebbleBit:webviewclosed()");

    var payload = JSON.parse(decodeURIComponent(e.response));

    console.log(JSON.stringify(payload));

    window.localStorage.clear();

    window.localStorage.setItem("accessToken", payload.accessToken);
    window.localStorage.setItem("accessTokenSecret", payload.accessTokenSecret);
    window.localStorage.setItem("steps", payload.steps);

    sendPebbleStepsAppMessage(payload.steps);
};

var getSteps = function () {
    console.log("PebbleBit:getSteps()");

    sendPebbleStatusAppMessage("...");

    var url = "https://pebblebit.azurewebsites.net/steps";

    // url += "?pebble=1";
    url += "?access_token=" + window.localStorage.getItem("accessToken");
    url += "&access_token_secret=" + window.localStorage.getItem("accessTokenSecret");

    console.log(url);

    var request = new XMLHttpRequest();

    request.onerror = function (e) {
        console.log("PebbleBit:getSteps:error()");

        var ejson = JSON.stringify(e);

        console.log(ejson);

        sendPebbleErrorAppMessage("E1");
    };

    request.onload = function (e) {
        console.log("PebbleBit:getSteps:onload()");

        var ejson = JSON.stringify(e);

        console.log(ejson);

        if (request.readyState !== 4) {
            console.log("readyState !== 4");
            return;
        }

        if (request.status !== 200) {
            console.log("HTTP Status");
            console.log(request.status);

            sendPebbleErrorAppMessage("E2");
            return;
        }

        console.log(request.responseText);

        var payload = JSON.parse(request.responseText);

        sendPebbleStepsAppMessage(payload.steps);
    };

    sendPebbleStatusAppMessage("..");

    request.open("GET", url, true);
    request.send(null);
};

var appmessage = function (e) {
    console.log("PebbleBit:appmessage()");

    if (e.payload.steps) {
        getSteps();
    }
};

// Set up event handlers.
Pebble.addEventListener("ready", ready);
Pebble.addEventListener("showConfiguration", showConfiguration);
Pebble.addEventListener("webviewclosed", webviewclosed);
Pebble.addEventListener("appmessage", appmessage);

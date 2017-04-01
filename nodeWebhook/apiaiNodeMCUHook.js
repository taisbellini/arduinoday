'use strict';
const express = require('express');
const bodyParser = require('body-parser');
const request = require('request');
const path = require('path');

// The rest of the code implements the routes for our Express server.
let app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: true
}));

const pins = {
  'red': 5,
  'green': 4,
  'lamp': 0
}


// Message processing
app.post('/webhook', function (req, res) {
   console.log(req.body);
  var data = req.body.result;
  let pin = 1;
  let color = data.parameters.color;
  let action = data.action;
  if (!color) {
    pin = pins['lamp'];
    // reverse logic of rele
    if (action == 'lights_off') {
      action = 'lights_on';
    } else {
      action = 'lights_off';
    }
  } else {
    pin = pins[color];
  }

  const params = {
    url: `https://5bd82048.ngrok.io/${action}`,
    qs: {
      pin
    }
  }
  console.log(params);
  request.get(params, (err,httpResponse,body) => {
    console.log('err', err);
    console.log('response', httpResponse);
    //console.log('body', body);

    res.sendStatus(200);
  });


});

// Set Express to listen out for HTTP requests
var server = app.listen(process.env.PORT || 5000, function () {
  console.log("Listening on port %s", server.address().port);
});

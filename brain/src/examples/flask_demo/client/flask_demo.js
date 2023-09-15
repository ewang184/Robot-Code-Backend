// Use this script in browser console
// repeatedly sends requests to an endpoint
while(true) {
    fetch("https://raspberrypi.local:5000/r").then((response) => response.json()).then((json) => console.log("output: " + json.output));
    const delay = (ms = 1000) => new Promise(r => setTimeout(r, ms));
    await delay();
}

async function loadState() {
    const response = await fetch("/api");
    const data = await response.json();
    document.getElementById("status").innerText =
        data.currentTime;

    document.getElementById("textInput").placeholder = data.timeOn;
    document.getElementById("textInput2").placeholder = data.timeOff;
}

async function setLed(state) {
    await fetch(state ? "/on" : "/off");
    loadState();
}

async function sendText() {
    const text1 = document.getElementById("textInput").value;
    const text2 = document.getElementById("textInput2").value;

    await fetch(`/sendText?value1=${encodeURIComponent(text1)}&value2=${encodeURIComponent(text2)}`);
    
    console.log("Sent:", text1, text2);
    document.getElementById("textInput").value = "";
    document.getElementById("textInput2").value = "";

    // const text = document.getElementById("textInput").value;
    // await fetch("/sendText?value=" + encodeURIComponent(text));
    // console.log("Sent:", text);
    // document.getElementById("textInput").value = "";
}

setInterval(loadState, 1000);
loadState();
// client.js

// Function to fetch data from ESP32 server and update dustbin color
async function updateDustbinColor() {
  try {
    // Make a GET request to ESP32 server
    const response = await fetch("http://esp32-server-ip/data");
    const data = await response.json();

    // Determine color based on received data
    let color;
    if (data.fillLevel === "low") {
      color = "red";
    } else if (data.fillLevel === "medium") {
      color = "yellow";
    } else if (data.fillLevel === "high") {
      color = "green";
    }

    // Update dustbin color
    const dustbin = document.getElementById("dustbin");
    dustbin.style.backgroundColor = color;
  } catch (error) {
    console.error("Error fetching data:", error);
  }
}

// Update dustbin color initially and every 5 seconds
updateDustbinColor();
setInterval(updateDustbinColor, 5000);

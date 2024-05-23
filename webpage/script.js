// Function to update the status box
function updateStatus(isOnline) {
    const statusBox = document.getElementById('status-box');
    if (isOnline) {
        statusBox.classList.remove('offline');
        statusBox.classList.add('online');
        statusBox.textContent = 'Server Online';
    } else {
        statusBox.classList.remove('online');
        statusBox.classList.add('offline');
        statusBox.textContent = 'Server Offline';
    }
}

// Function to fetch data from the server
async function fetchData() {
    try {
        let response = await fetch('http://192.168.1.45/');
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        let data = await response.json();
        document.getElementById('voltage').innerText = data.value1;
        document.getElementById('lux').innerText = data.value2;
        updateStatus(true); // Server is online
    } catch (error) {
        console.error('Error fetching data:', error);
        updateStatus(false); // Server is offline
    }
}

// Fetch data every second
setInterval(fetchData, 1000);

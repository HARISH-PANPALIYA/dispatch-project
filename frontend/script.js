// --- Global State & Map Initialization ---

const PUNE_COORDS = [18.5204, 73.8567]; // Pune, India
const API_URL = 'http://localhost:18080/api';

var map = L.map('mapid').setView(PUNE_COORDS, 12);
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    maxZoom: 19,
    attribution: '© OpenStreetMap contributors'
}).addTo(map);

let incidentMarker = null; // Marker for a new incident being reported
let mapClickListener = null; // Stores the map click handler
let activeMarkers = []; // Stores all existing unit and incident markers
let activeRoutes = []; // Stores all drawn routes

// Custom Icon definitions
const getIcon = (color, text) => L.divIcon({
    className: `custom-div-icon ${color}`,
    html: `<div style="background-color:${color}; width: 12px; height: 12px; border-radius: 50%; border: 2px solid white;"></div><span style="font-size:10px; font-weight:bold; color:black;">${text}</span>`,
    iconSize: [40, 40],
    iconAnchor: [6, 18]
});

// --- UI Logic ---

function centerMap() {
    map.setView(PUNE_COORDS, 12);
}

function startNewIncident() {
    // Disable the button and add a temporary instruction
    document.getElementById('report-btn').disabled = true;
    document.getElementById('report-btn').textContent = "Click on Map Location...";

    // Enable map click listener
    mapClickListener = map.on('click', handleMapClick);
}

function handleMapClick(e) {
    if (incidentMarker) {
        map.removeLayer(incidentMarker);
    }
    
    // Place a temporary marker
    incidentMarker = L.marker(e.latlng).addTo(map);

    // Show the incident form
    document.getElementById('incident-coords').textContent = `${e.latlng.lat.toFixed(4)}, ${e.latlng.lng.toFixed(4)}`;
    document.getElementById('incident-form-overlay').classList.remove('hidden');

    // Disable the map click listener once location is selected
    map.off('click', mapClickListener);
}

function cancelReport() {
    if (incidentMarker) {
        map.removeLayer(incidentMarker);
        incidentMarker = null;
    }
    document.getElementById('incident-form-overlay').classList.add('hidden');
    document.getElementById('report-btn').disabled = false;
    document.getElementById('report-btn').textContent = "Report New Incident";
}

// --- API and Core Dispatch Logic ---

async function reportAndDispatch() {
    if (!incidentMarker) return;

    const lat = incidentMarker.getLatLng().lat;
    const lon = incidentMarker.getLatLng().lng;
    const details = document.getElementById('incident-details').value;

    const incidentData = {
        latitude: lat,
        longitude: lon,
        details: details
    };
    
    try {
        // Send request to the C++ Backend Service
        const response = await fetch(`${API_URL}/dispatch`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(incidentData),
        });

        if (!response.ok) {
            const errorText = await response.text();
            throw new Error(`Dispatch Failed: ${response.statusText}. Details: ${errorText}`);
        }

        const data = await response.json();
        
        // 4. Action and Visualization (Draw Route)
        const pathCoords = data.path.map(c => [c[0], c[1]]); // Convert [[lat, lon], ...]
        const route = L.polyline(pathCoords, {color: '#cc0000', weight: 4, opacity: 0.7}).addTo(map);
        activeRoutes.push(route);
        
        alert(`Unit ${data.unit_id} (${data.unit_name}) dispatched. Route shown.`);
        
        cancelReport(); // Reset UI
        refreshMapData(); // Get the new status of all units/incidents

    } catch (error) {
        console.error("Dispatch Error:", error);
        alert(`Error during dispatch: ${error.message}`);
    }
}

// Polling function to get the current state of the system
async function refreshMapData() {
    try {
        const response = await fetch(`${API_URL}/data/refresh`);
        if (!response.ok) throw new Error("Could not fetch refresh data from C++ backend.");
        
        const data = await response.json();
        
        // 1. Clear previous markers and routes
        activeMarkers.forEach(m => map.removeLayer(m));
        activeRoutes.forEach(r => map.removeLayer(r));
        activeMarkers = [];
        activeRoutes = [];

        // 2. Update status counts
        document.getElementById('unit-count').textContent = data.units.length;
        document.getElementById('incident-count').textContent = data.incidents.filter(i => i.status === 'active' || i.status === 'assigned').length;

        // 3. Draw Units
        data.units.forEach(unit => {
            let color = unit.status === 'available' ? 'green' : (unit.status === 'dispatched' ? 'orange' : 'gray');
            let icon = getIcon(color, unit.name);
            let marker = L.marker([unit.current_latitude, unit.current_longitude], {icon: icon})
                .bindPopup(`<b>Unit: ${unit.name}</b><br>Type: ${unit.type}<br>Status: ${unit.status}`);
            marker.addTo(map);
            activeMarkers.push(marker);
        });

        // 4. Draw Incidents
        data.incidents.forEach(incident => {
            if (incident.status === 'active' || incident.status === 'assigned') {
                let icon = getIcon('red', `INC-${incident.id}`);
                let marker = L.marker([incident.latitude, incident.longitude], {icon: icon})
                    .bindPopup(`<b>Incident #${incident.id}</b><br>Details: ${incident.details}<br>Status: ${incident.status}<br>Assigned Unit: ${incident.assigned_unit_id || 'N/A'}`);
                marker.addTo(map);
                activeMarkers.push(marker);
            }
        });

    } catch (error) {
        console.error("Refresh Error:", error);
        document.getElementById('status-box').innerHTML = `<p style="color:red;">CONNECTION ERROR</p>`;
    }
}

// Initial data load when the page loads
document.addEventListener('DOMContentLoaded', () => {
    refreshMapData();
    // Start automatic polling every 5 seconds for single-user 'real-time' simulation
    setInterval(refreshMapData, 5000); 
});
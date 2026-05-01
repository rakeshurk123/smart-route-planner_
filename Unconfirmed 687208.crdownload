let graphMatrix = [];

// Generate graph matrix input fields
function generateGraph() {
    const citiesInput = document.getElementById('cities');
    const cities = parseInt(citiesInput.value);

    if (isNaN(cities) || cities < 2 || cities > 10) {
        showError('Please enter a number between 2 and 10');
        return;
    }

    graphMatrix = Array(cities).fill().map(() => Array(cities).fill(0));

    const matrixContainer = document.getElementById('matrixContainer');
    matrixContainer.innerHTML = '';

    const title = document.createElement('p');
    title.style.cssText = 'font-weight: 600; margin-bottom: 15px; color: #667eea;';
    title.textContent = `📊 Distance Matrix (${cities}×${cities})`;
    matrixContainer.appendChild(title);

    for (let i = 0; i < cities; i++) {
        const row = document.createElement('div');
        row.className = 'matrix-row';

        const label = document.createElement('label');
        label.style.gridColumn = '1 / -1';
        label.textContent = `From City ${i}:`;
        row.appendChild(label);

        for (let j = 0; j < cities; j++) {
            const inputWrapper = document.createElement('div');
            const input = document.createElement('input');
            input.type = 'number';
            input.min = '0';
            input.max = '1000';
            input.value = '0';
            input.placeholder = `→ ${j}`;
            input.style.cssText = 'width: 100%;';
            
            input.addEventListener('input', (e) => {
                graphMatrix[i][j] = parseInt(e.target.value) || 0;
            });

            inputWrapper.appendChild(input);
            row.appendChild(inputWrapper);
        }

        matrixContainer.appendChild(row);
    }

    // Update source node max value
    document.getElementById('sourceNode').max = cities - 1;
    document.getElementById('sourceNode').value = 0;

    showSuccess(`Graph created for ${cities} cities`);
}

// Calculate shortest paths
async function calculatePaths() {
    const sourceNode = parseInt(document.getElementById('sourceNode').value);
    const cities = parseInt(document.getElementById('cities').value);

    if (isNaN(sourceNode) || sourceNode < 0 || sourceNode >= cities) {
        showError('Invalid source node');
        return;
    }

    if (graphMatrix.length === 0) {
        showError('Please generate graph first');
        return;
    }

    try {
        const response = await fetch('http://localhost:3000/api/shortest-paths', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                graph: graphMatrix,
                source: sourceNode
            })
        });

        if (!response.ok) {
            throw new Error('Failed to calculate paths');
        }

        const data = await response.json();
        displayResults(data);
        updateStatistics(data);
    } catch (error) {
        showError('Error: ' + error.message);
    }
}

// Display results
function displayResults(data) {
    const resultsContainer = document.getElementById('resultsContainer');
    resultsContainer.innerHTML = '';

    const header = document.createElement('div');
    header.style.cssText = 'font-weight: 700; color: #667eea; margin-bottom: 15px; padding-bottom: 10px; border-bottom: 2px solid #667eea;';
    header.textContent = `Routes from City ${data.source}:`;
    resultsContainer.appendChild(header);

    data.routes.forEach((route) => {
        const item = document.createElement('div');
        item.className = 'result-item';

        const destination = document.createElement('div');
        destination.className = 'destination';
        destination.textContent = `City ${route.destination}`;

        const distance = document.createElement('div');
        distance.className = 'distance';
        distance.textContent = `Distance: ${route.distance === 'Unreachable' ? '∞ (Unreachable)' : route.distance}`;

        const pathDiv = document.createElement('div');
        pathDiv.style.marginBottom = '8px';
        const pathLabel = document.createElement('span');
        pathLabel.style.cssText = 'font-weight: 600; color: #667eea; display: block; margin-bottom: 5px;';
        pathLabel.textContent = 'Path:';
        pathDiv.appendChild(pathLabel);

        const path = document.createElement('div');
        path.className = 'path';
        path.textContent = route.path.join(' → ');
        pathDiv.appendChild(path);

        item.appendChild(destination);
        item.appendChild(distance);
        item.appendChild(pathDiv);

        resultsContainer.appendChild(item);
    });

    displayVisualization(data);
}

// Visualize paths
function displayVisualization(data) {
    const visualization = document.getElementById('pathVisualization');
    visualization.innerHTML = '';

    const header = document.createElement('div');
    header.style.cssText = 'font-weight: 700; color: #667eea; margin-bottom: 15px;';
    header.textContent = `All Routes from City ${data.source}`;
    visualization.appendChild(header);

    const container = document.createElement('div');
    container.style.cssText = 'display: flex; flex-direction: column; gap: 12px;';

    data.routes.forEach((route) => {
        const pathItem = document.createElement('div');
        pathItem.className = 'path-item';

        const pathInfo = document.createElement('div');
        pathInfo.className = 'path-info';
        
        const dest = document.createElement('div');
        dest.style.cssText = 'font-weight: 600; color: #333; margin-bottom: 8px;';
        dest.textContent = `To City ${route.destination}`;
        pathInfo.appendChild(dest);

        const pathNodes = document.createElement('div');
        pathNodes.className = 'path-nodes';
        pathNodes.textContent = route.path.join(' → ');
        pathInfo.appendChild(pathNodes);

        const badge = document.createElement('div');
        badge.className = 'distance-badge';
        badge.textContent = route.distance === 'Unreachable' ? '∞' : route.distance;

        pathItem.appendChild(pathInfo);
        pathItem.appendChild(badge);
        container.appendChild(pathItem);
    });

    visualization.appendChild(container);
}

// Update statistics
function updateStatistics(data) {
    const cities = data.routes.length;
    const reachable = data.routes.filter(r => r.distance !== 'Unreachable').length;

    document.getElementById('totalCities').textContent = cities;
    document.getElementById('sourceDisplay').textContent = data.source;
    document.getElementById('reachable').textContent = reachable + ' / ' + cities;
    document.getElementById('algorithm').textContent = data.algorithm;
}

// Reset form
function resetForm() {
    document.getElementById('cities').value = '4';
    document.getElementById('sourceNode').value = '0';
    document.getElementById('matrixContainer').innerHTML = '';
    document.getElementById('resultsContainer').innerHTML = 
        '<div class="placeholder"><p>Configure graph and click "Calculate Shortest Paths" to see results</p></div>';
    document.getElementById('pathVisualization').innerHTML = 
        '<div class="placeholder"><p>Paths will be visualized here</p></div>';
    
    document.getElementById('totalCities').textContent = '-';
    document.getElementById('sourceDisplay').textContent = '-';
    document.getElementById('reachable').textContent = '-';

    graphMatrix = [];
    showSuccess('Form reset');
}

// Helper functions
function showError(message) {
    const notification = document.createElement('div');
    notification.className = 'error';
    notification.textContent = '❌ ' + message;
    document.querySelector('.main-content').insertBefore(
        notification, 
        document.querySelector('.main-content').firstChild
    );

    setTimeout(() => notification.remove(), 4000);
}

function showSuccess(message) {
    const notification = document.createElement('div');
    notification.className = 'success';
    notification.textContent = '✅ ' + message;
    document.querySelector('.main-content').insertBefore(
        notification, 
        document.querySelector('.main-content').firstChild
    );

    setTimeout(() => notification.remove(), 3000);
}

// Initialize with default graph on page load
window.addEventListener('load', () => {
    generateGraph();
    loadCCode();
});

// Load C Code
async function loadCCode() {
    try {
        const response = await fetch('/original-code.c');
        const cCode = await response.text();
        document.getElementById('codeDisplay').textContent = cCode;
    } catch (error) {
        document.getElementById('codeDisplay').textContent = '// Unable to load C code\n// Please check if original-code.c exists';
    }
}

// Toggle C Code visibility
function toggleCCode() {
    const container = document.getElementById('codeContainer');
    if (container.style.display === 'none') {
        container.style.display = 'block';
    } else {
        container.style.display = 'none';
    }
}

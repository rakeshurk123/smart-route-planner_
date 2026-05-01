const express = require('express');
const cors = require('cors');
const path = require('path');
const fs = require('fs');

const app = express();
const PORT = 3000;

// Middleware
app.use(cors());
app.use(express.json());
app.use(express.static('public'));

// Serve original C code
app.get('/original-code.c', (req, res) => {
    const cCodePath = path.join(__dirname, 'original-code.c');
    fs.readFile(cCodePath, 'utf8', (err, data) => {
        if (err) {
            res.status(404).send('C code file not found');
            return;
        }
        res.type('text/plain').send(data);
    });
});

// Dijkstra's Algorithm Implementation
function dijkstra(graph, source) {
    const n = graph.length;
    const distances = Array(n).fill(Infinity);
    const visited = Array(n).fill(false);
    const parents = Array(n).fill(-1);

    distances[source] = 0;

    for (let count = 0; count < n - 1; count++) {
        let minDist = Infinity;
        let u = -1;

        // Find minimum distance unvisited vertex
        for (let i = 0; i < n; i++) {
            if (!visited[i] && distances[i] < minDist) {
                minDist = distances[i];
                u = i;
            }
        }

        if (u === -1) break;

        visited[u] = true;

        // Update distances of adjacent vertices
        for (let v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] > 0 && 
                distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];
                parents[v] = u;
            }
        }
    }

    return { distances, parents };
}

// Function to reconstruct path
function getPath(parents, destination) {
    const path = [];
    let current = destination;

    while (current !== -1) {
        path.unshift(current);
        current = parents[current];
    }

    return path.length > 1 ? path : [destination];
}

// API Endpoint: Calculate shortest paths
app.post('/api/shortest-paths', (req, res) => {
    try {
        const { graph, source } = req.body;

        if (!graph || source === undefined) {
            return res.status(400).json({ error: 'Graph and source are required' });
        }

        if (source < 0 || source >= graph.length) {
            return res.status(400).json({ error: 'Invalid source node' });
        }

        const { distances, parents } = dijkstra(graph, source);
        const n = graph.length;
        const routes = [];

        for (let i = 0; i < n; i++) {
            const path = getPath(parents, i);
            routes.push({
                destination: i,
                distance: distances[i] === Infinity ? 'Unreachable' : distances[i],
                path: path
            });
        }

        res.json({
            source,
            routes,
            algorithm: 'Dijkstra'
        });
    } catch (error) {
        res.status(500).json({ error: 'Server error: ' + error.message });
    }
});

// Health check endpoint
app.get('/api/health', (req, res) => {
    res.json({ status: 'Server is running' });
});

// Start server
app.listen(PORT, () => {
    console.log(`\n==========================================`);
    console.log(`Smart Route Planner Server Running`);
    console.log(`==========================================`);
    console.log(`Server is running on http://localhost:${PORT}`);
    console.log(`==========================================\n`);
});

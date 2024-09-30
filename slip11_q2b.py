import heapq

# Define the graph as an adjacency dictionary
graph = {
    'A': {'B': 6, 'F': 3},
    'B': {'C': 3, 'D': 7},
    'C': {'D': 1, 'E':5},
    'D': {'E': 8},
    'E': {'J': 5, 'I': 5},
    'F': {'G': 1, 'H': 7},
    'G': {'I': 3},
    'H': {'I': 2},
    'I': {'E': 5, 'J': 3, 'H': 2},
    'J': {}
}

# Heuristic function (for A* algorithm)
heuristic = {
    'A': 10,
    'B': 8,
    'C': 5,
    'D': 7,
    'F': 6,
    'G': 5,
    'I': 1,
    'E': 3,
    'H': 3,
    'J': 0
}

def astar(graph, start, goal):
    open_set = [(0, start)]  # Priority queue (f-score, node)
    came_from = {}           # Dictionary to store the parent node for each node
    g_score = {node: float('inf') for node in graph}
    g_score[start] = 0

    while open_set:
        _, current = heapq.heappop(open_set)

        if current == goal:
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            path.reverse()
            return path

        for neighbor, cost in graph[current].items():
            tentative_g_score = g_score[current] + cost
            if tentative_g_score < g_score[neighbor]:
                came_from[neighbor] = current
                g_score[neighbor] = tentative_g_score
                f_score = tentative_g_score + heuristic[neighbor]
                heapq.heappush(open_set, (f_score, neighbor))

    return None  # No path found

start_node = 'A'
goal_node = 'J'
shortest_path = astar(graph, start_node, goal_node)

if shortest_path:
    print("Shortest Path:", shortest_path)
else:
    print("No path found.")
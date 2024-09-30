import heapq

# Define the graph as an adjacency list
graph = {
    'A': [('B', 4), ('D', 5)],
    'B': [('C', 2)],
    'C': [('E', 2)],
    'D': [('E', 2), ('F', 4)],
    'E': [('F', 3)],
    'F': []
  
}

# Define a heuristic function (for simplicity, use a dictionary)
heuristic = {
    'A': 8,
    'B': 1,
    'C': 2,
    'D': 8,
    'E': 1,
    'F': 0
}

# Define the AO* algorithm
def ao_star(graph, start, goal, heuristic):
    open_list = [(0, start)]  # Priority queue (cost, node)
    closed_list = set()
    g_values = {node: float('inf') for node in graph}
    g_values[start] = 0
    parent = {node: None for node in graph}

    while open_list:
        _, current = heapq.heappop(open_list)

        if current == goal:
            # Reconstruct the path
            path = []
            while current:
                path.append(current)
                current = parent[current]
            return path[::-1]  # Reverse the path to get it from start to goal

        if current in closed_list:
            continue

        closed_list.add(current)

        for neighbor, cost in graph[current]:
            if neighbor in closed_list:
                continue

            tentative_g = g_values[current] + cost

            if tentative_g < g_values[neighbor]:
                g_values[neighbor] = tentative_g
                f_value = tentative_g + heuristic[neighbor]
                heapq.heappush(open_list, (f_value, neighbor))
                parent[neighbor] = current

    return None  # No path found

# Find the minimum cost path from 'A' to 'D'
start_node = 'A'
goal_node = 'F'
path = ao_star(graph, start_node, goal_node, heuristic)

if path:
    print(f"Minimum cost path from {start_node} to {goal_node}: {' -> '.join(path)}")
else:
    print("No path found.")
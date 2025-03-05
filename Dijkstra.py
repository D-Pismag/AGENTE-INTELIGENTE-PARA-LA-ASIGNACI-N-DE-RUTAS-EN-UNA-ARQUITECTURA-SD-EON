import heapq
import numpy as np
import time

# Definición de los grafos
#Grafo de distancias entre nodos adyacentes
graph = {
    'Nodo1': {'Nodo2': 2100, 'Nodo3': 3000, 'Nodo8': 4800},
    'Nodo2': {'Nodo1': 2100, 'Nodo3': 1200, 'Nodo4': 1500},
    'Nodo3': {'Nodo1': 3000, 'Nodo2': 1200, 'Nodo6': 3600},
    'Nodo4': {'Nodo2': 1500, 'Nodo5': 1200, 'Nodo11': 3900},
    'Nodo5': {'Nodo4': 1500, 'Nodo6': 2400, 'Nodo7': 1200}, 
    'Nodo6': {'Nodo3': 3600, 'Nodo5': 2400, 'Nodo10': 2100, 'Nodo14': 3600},
    'Nodo7': {'Nodo5': 1200, 'Nodo8': 1500},
    'Nodo8': {'Nodo1': 4800, 'Nodo7': 1500, 'Nodo9': 1500},
    'Nodo9': {'Nodo8': 1500, 'Nodo10': 1500, 'Nodo12': 600, 'Nodo13': 600},
    'Nodo10': {'Nodo6': 2100, 'Nodo9': 1500},
    'Nodo11': {'Nodo4': 3900, 'Nodo12': 1200, 'Nodo13': 1500},
    'Nodo12': {'Nodo9': 600, 'Nodo11': 1200, 'Nodo14': 600},
    'Nodo13': {'Nodo9': 600, 'Nodo11': 1500, 'Nodo14': 300},
    'Nodo14': {'Nodo6': 3600, 'Nodo12': 600, 'Nodo13': 300},
}
#Grafo de interfaces de entrada
graphIE = {
    'Nodo1': {'Nodo2': ('1'), 'Nodo3': ('2'), 'Nodo8': ('3')},
    'Nodo2': {'Nodo1': ('1'), 'Nodo3': ('3'), 'Nodo4': ('2')},
    'Nodo3': {'Nodo1': ('2'), 'Nodo2': ('3'), 'Nodo6': ('1')},
    'Nodo4': {'Nodo2': ('2'), 'Nodo5': ('1'), 'Nodo11': ('3')},
    'Nodo5': {'Nodo4': ('1'), 'Nodo6': ('3'), 'Nodo7': ('2')}, 
    'Nodo6': {'Nodo3': ('1'), 'Nodo5': ('3'), 'Nodo10': ('2'), 'Nodo14': ('4')},
    'Nodo7': {'Nodo5': ('2'), 'Nodo8': ('1')},
    'Nodo8': {'Nodo1': ('3'), 'Nodo7': ('1'), 'Nodo9': ('2')},
    'Nodo9': {'Nodo8': ('2'), 'Nodo10': ('1'), 'Nodo12': ('3'), 'Nodo13': ('4')},
    'Nodo10': {'Nodo6': ('2'), 'Nodo9': ('1')},
    'Nodo11': {'Nodo4': ('3'), 'Nodo12': ('1'), 'Nodo13': ('2')},
    'Nodo12': {'Nodo9': ('3'), 'Nodo11': ('1'), 'Nodo14': ('2')},
    'Nodo13': {'Nodo9': ('4'), 'Nodo11': ('2'), 'Nodo14': ('3')},
    'Nodo14': {'Nodo6': ('4'), 'Nodo12': ('2'), 'Nodo13': ('3')},
}
#Grafo de interfaces de salida
graphIS = {
    'Nodo1': {'Nodo2': ('1'), 'Nodo3': ('2'), 'Nodo8': ('3')},
    'Nodo2': {'Nodo1': ('1'), 'Nodo3': ('3'), 'Nodo4': ('2')},
    'Nodo3': {'Nodo1': ('2'), 'Nodo2': ('3'), 'Nodo6': ('1')},
    'Nodo4': {'Nodo2': ('2'), 'Nodo5': ('1'), 'Nodo11': ('3')},
    'Nodo5': {'Nodo4': ('1'), 'Nodo6': ('3'), 'Nodo7': ('2')}, 
    'Nodo6': {'Nodo3': ('1'), 'Nodo5': ('3'), 'Nodo10': ('2'), 'Nodo14': ('4')},
    'Nodo7': {'Nodo5': ('2'), 'Nodo8': ('1')},
    'Nodo8': {'Nodo1': ('3'), 'Nodo7': ('1'), 'Nodo9': ('2')},
    'Nodo9': {'Nodo8': ('2'), 'Nodo10': ('1'), 'Nodo12': ('3'), 'Nodo13': ('4')},
    'Nodo10': {'Nodo6': ('2'), 'Nodo9': ('1')},
    'Nodo11': {'Nodo4': ('3'), 'Nodo12': ('1'), 'Nodo13': ('2')},
    'Nodo12': {'Nodo9': ('3'), 'Nodo11': ('1'), 'Nodo14': ('2')},
    'Nodo13': {'Nodo9': ('4'), 'Nodo11': ('2'), 'Nodo14': ('3')},
    'Nodo14': {'Nodo6': ('4'), 'Nodo12': ('2'), 'Nodo13': ('3')},
}

# Función para implementar el algoritmo de Dijkstra
def dijkstra(graph, start_node, end_node):
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    priority_queue = [(0, start_node)]
    previous_nodes = {node: None for node in graph}

    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)

        if current_node == end_node:
            path = []
            while current_node is not None:
                path.append(current_node)
                current_node = previous_nodes[current_node]
            return path[::-1], distances[end_node]

        if current_distance > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node].items():
            distance = current_distance + weight

            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous_nodes[neighbor] = current_node
                heapq.heappush(priority_queue, (distance, neighbor))

    return None, float('inf')

# Función para imprimir la ruta con interfaces
def print_route_with_interfaces(route):
    route_info = [] 
    for i in range(len(route) - 1):
        current_node = route[i]
        next_node = route[i + 1]
        
        input_interface = graphIE[route[i - 1]][current_node] if i > 0 else "0"
        output_interface = graphIS[current_node][next_node]
        route_info.append(f"[0,{route[0]},{output_interface}]") if i == 0 else None
        route_info.append(f"[{input_interface},{current_node},{output_interface}]") if i > 0 else None

    final_node = route[-1]
    input_interface_final = graphIE[route[-2]][final_node] if len(route) > 1 else "0"
    route_info.append(f"[{input_interface_final},{final_node},0]")
    return ";".join(route_info)

# Función principal modificada
def main():
    start_node = input("Ingrese el nodo de inicio para el algoritmo: ")
    end_node = input("Ingrese el nodo de destino para el algoritmo: ")
    # Preguntar al usuario el tipo de mensaje
    message_type = input("Ingrese el tipo de mensaje (1, 2 o 3): ")

    # Inicia la medición del tiempo
    start_time = time.time()
    # Ejecutar Dijkstra
    best_route, total_distance = dijkstra(graph, start_node, end_node)
    # Imprimir resultados según el tipo de mensaje
    
    def handle_message_type_1():
        if best_route is not None:
            formatted_route = print_route_with_interfaces(best_route)
            print(f"Ruta Optima: {formatted_route}")
        else:
            print("No hay ruta disponible entre los nodos especificados.")

    def handle_message_type_2():
        if best_route is not None:
            formatted_route = print_route_with_interfaces(best_route)
            print(f"Ruta: {formatted_route}")
        else:
            print("No hay ruta disponible entre los nodos especificados.")

    def handle_message_type_3():
        if best_route is not None:
            formatted_route = print_route_with_interfaces(best_route)
            print(f"Ruta Optima: {formatted_route}")
            print(f"Ruta: {formatted_route}")
        else:
            print("No hay ruta disponible entre los nodos especificados.")

    # Mapeo de tipos de mensaje a funciones
    message_handlers = {
        '1': handle_message_type_1,
        '2': handle_message_type_2,
        '3': handle_message_type_3
    }

    # Llamar a la función correspondiente según el tipo de mensaje
    handler = message_handlers.get(message_type)
    if handler:
        handler()
    else:
        print("Tipo de mensaje no válido. Por favor, ingrese 1, 2 o 3.")

    end_time = time.time()
    # Calcula y muestra el tiempo total de simulación
    simulation_time = (end_time - start_time) * 1000
    print(f"Tiempo de simulación: {simulation_time:.2f} milisegundos")  # Finaliza la medición del tiempo

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"Ocurrió un error: {e}")
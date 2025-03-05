import random
import numpy as np
import time
import json
import os
import sys

# Grafo predefinido
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

class ResultDatabase:
    def __init__(self, filename='results.json'):
        self.filename = filename
        self.results = self.load_results()

    def load_results(self):
        if os.path.exists(self.filename):
            with open(self.filename, 'r') as json_file:
                return json.load(json_file)
        return {}

    def update_results(self, start_node, end_node, best_routes):
        key = f"{start_node}_{end_node}"
        if key not in self.results:
            self.results[key] = {'best_routes': []}

        # Agregar las nuevas mejores rutas
        for new_route in best_routes:
            if not any(existing_route['path'] == new_route['path'] for existing_route in self.results[key]['best_routes']):
                self.results[key]['best_routes'].append(new_route)

        # Mantener solo las 5 mejores rutas
        self.results[key]['best_routes'] = sorted(self.results[key]['best_routes'], key=lambda x: x['distance'])[:5]

        self.save_results()

    def save_results(self):
        with open(self.filename, 'w') as json_file:
            json.dump(self.results, json_file, indent=4)

    def compare_results(self, new_results, old_results):
        comparison = {}
        for key in new_results:
            if key in old_results:
                comparison[key] = {
                    'new': new_results[key],
                    'old': old_results[key],
                    'better': new_results[key]['distance'] < old_results[key]['distance']  # Comparar según la distancia
                }
            else:
                comparison[key] = {
                    'new': new_results[key],
                    'old': None,
                    'better': None
                }
        return comparison

class GeneticAlgorithm:
    def __init__(self, graph, graphIE, graphIS, start_node, end_node, population_size, generations):
        self.graph = graph
        self.graphIE = graphIE
        self.graphIS = graphIS
        self.start_node = start_node
        self.end_node = end_node
        self.population_size = population_size
        self.generations = generations
        self.mutation_rate = 0.01
        self.result_db = ResultDatabase()
        self.population = self.initialize_population()
        self.best_routes = []  # Lista para almacenar las mejores rutas
        self.initial_routes = self.population.copy()  # Almacena las rutas iniciales
        self.result_db = ResultDatabase()

    def initialize_population(self):
        population = []
        for _ in range(self.population_size):
            route = self.create_random_route()
            population.append(route) 
        return population
         
    def create_random_route(self):
        route = [self.start_node]
        attempts = 0
        max_attempts = 15 # Limitar el número de intentos para evitar bucles infinitos

        while attempts < max_attempts:
            if route[-1] == self.end_node:
                break
            next_nodes = [node for node in self.graph[route[-1]].keys() if node not in route]
        
            if not next_nodes:
                return self.create_random_route()
        
            next_node = random.choice(next_nodes)
            route.append(next_node)
            attempts += 1

        if route[-1] != self.end_node:
            route.append(self.end_node) # Asegúra que la ruta termine en el nodo de destino
        return route

    def fitness(self, route):
        # Verificar si la ruta termina en el nodo de destino
        if route[-1] != self.end_node:
            return float('inf'), float('inf') # Penaliza rutas inválidas

        distance = 0
        for i in range(len(route) - 1):
            # Verificar si hay una conexión entre los nodos
            if route[i + 1] in self.graph[route[i]]:
                distance += self.graph[route[i]][route[i + 1]]
            else:
                return float('inf'), float('inf') # Penaliza si no hay conexión

        num_nodes_intermediate = len(route) - 2  #Excluir nodos de inicio y fin
        return distance, num_nodes_intermediate # Retorna ambos objetivos
    
    def select(self):
        total_fitness = sum(1 / (self.fitness(individual )[0] + 1e-6) for individual in self.population) # Sumar fitness inverso
        pick = random.uniform(0, total_fitness) # Elegir un número aleatorio entre 0 y la suma total de fitness
        current = 0

        for individual in self.population:
            fitness_value = 1 / (self.fitness(individual)[0] + 1e-6) # Fitness inverso
            current += fitness_value
            if current > pick:
                return individual

    def crossover(self, parent1, parent2):
        excluded_nodes = {self.start_node, self.end_node} # Excluir nodos de origen y destino
        common_nodes = set(parent1) & set(parent2) - excluded_nodes # Encontrar nodos comunes excluyendo los nodos de origen y destino
    
        if not common_nodes:
            return random.choice([parent1, parent2])
        crossover_node = common_nodes.pop()
        crossover_index1 = parent1.index(crossover_node)
        crossover_index2 = parent2.index(crossover_node)
        child = parent1[:crossover_index1 + 1] + [node for node in parent2[crossover_index2 + 1:] if node not in parent1[:crossover_index1 + 1]]
        child = [self.start_node] + child
        if self.end_node not in child:
            child.append(self.end_node)
        child = self.validate_route(child)
        return child

    def validate_route(self, route):
        seen = set()
        valid_route = []
    
        for node in route:
            if node not in seen:
                valid_route.append(node)
                seen.add(node)

        if valid_route[0] != self.start_node:
            valid_route.insert(0, self.start_node)
        if valid_route[-1] != self.end_node:
            valid_route.append(self.end_node)

        return valid_route

    def mutate(self, route):
        if random.random() < self.mutation_rate:
            # Limitar el número total de nodos a 15
            if len(route) > 15:
                return route
            
            # Elegir un nodo intermedio aleatorio (excluyendo el inicio y el final)
            if len(route) > 2:
                intermediate_index = random.randint(1, len(route) - 2)
                intermediate_node = route[intermediate_index]
                previous_node = route[intermediate_index - 1]

                # Obtener nodos adyacentes al nodo anterior
                adjacent_nodes = list(self.graph[previous_node].keys())
                # Elegir un nodo adyacente que no sea el nodo intermedio
                adjacent_nodes = [node for node in adjacent_nodes if node != intermediate_node]

                if adjacent_nodes:
                    new_node = random.choice(adjacent_nodes)
                    # Reemplazar el nodo intermedio por el nuevo nodo
                    route[intermediate_index] = new_node

                    # Reconstruir la ruta a partir del nodo anterior
                    new_route = [self.start_node]
                    current_node = new_node
                    while current_node != self.end_node and len(new_route) < 15:
                        next_nodes = [node for node in self.graph[current_node].keys() if node not in new_route]
                        if not next_nodes:
                            break  # No hay más nodos para avanzar
                        current_node = random.choice(next_nodes)
                        new_route.append(current_node)

                    # Asegurarse de que la ruta termine en el nodo de destino
                    if new_route[-1] != self.end_node:
                        new_route.append(self.end_node)

                    # Validar la nueva ruta utilizando la función validate_route
                    if self.validate_route(new_route):
                        return new_route  # Retornar la nueva ruta mutada
                    else:
                        return self.mutate(route)  # Intentar de nuevo si no es válida
                else:
                    print("No hay nodos adyacentes disponibles para mutar.")
                    return route  # Retornar la ruta original si no hay nodos adyacentes
            else:
                # Si no hay nodos intermedios, elegir un adyacente al nodo de inicio
                adjacent_nodes = list(self.graph[self.start_node].keys())
                adjacent_nodes = [node for node in adjacent_nodes if node != self.end_node]

                if adjacent_nodes:
                    new_node = random.choice(adjacent_nodes)
                    new_route = [self.start_node, new_node]

                    # Completar la ruta hasta el nodo final
                    while new_route[-1] != self.end_node and len(new_route) < 15:
                        next_nodes = [node for node in self.graph[new_route[-1]].keys() if node not in new_route]
                        if not next_nodes:
                            break  # No hay más nodos para avanzar
                        new_route.append(random.choice(next_nodes))

                    # Asegurarse de que la ruta termine en el nodo de destino
                    if new_route[-1] != self.end_node:
                        new_route.append(self.end_node)

                    # Validar la nueva ruta utilizando la función validate_route
                    if self.validate_route(new_route):
                        return new_route  # Retornar la nueva ruta mutada
                    else:
                        return self.mutate(route)  # Intentar de nuevo si no es válida
                else:
                    print("No hay nodos adyacentes disponibles para iniciar la mutación.")
                    return route  # Retornar la ruta original si no hay nodos adyacentes
        #print("se completo una mutacion:", route)
        return route  # Si no se muta, retornar la ruta original
        
    def update_best_routes(self, new_route):
        unique_routes = {tuple(route): route for route in self.best_routes}
        for route in self.population:
            if tuple(route) not in unique_routes:
                unique_routes[tuple(route)] = route
        sorted_routes = sorted(unique_routes.values(), key=lambda r: self.fitness(r)[0])
        self.best_routes = sorted_routes[:5]  # Mantener solo las 2 mejores rutas

    def evolve(self):
        # Combinar la población actual con las rutas iniciales
        combined_population = self.population + self.initial_routes
        new_population = []
        
        for _ in range(self.population_size):
            parent1 = self.select_from_combined(combined_population)
            parent2 = self.select_from_combined(combined_population)
            child = self.crossover(parent1, parent2)
            self.mutate(child)
            if child[-1] == self.end_node:
                new_population.append(child)
        
        self.population = new_population

    def select_from_combined(self, combined_population):
        total_fitness = sum(1 / (self.fitness(individual)[0] + 1e-6) for individual in combined_population)
        pick = random.uniform(0, total_fitness)
        current = 0

        for individual in combined_population:
            fitness_value = 1 / (self.fitness(individual)[0] + 1e-6)
            current += fitness_value
            if current > pick:
                return individual
    
    def print_route_with_interfaces(self, route):
        route_info = [] 
        for i in range(len(route) - 1):  # Iterar hasta el penúltimo nodo
            current_node = route[i]
            next_node = route[i + 1]
        
            # Obtener la interfaz de entrada del nodo actual desde el nodo anterior
            input_interface = self.graphIE[route[i - 1]][current_node] if i > 0 else "0"
        
            # Obtener la interfaz de salida del nodo actual hacia el nodo siguiente
            output_interface = self.graphIS[current_node][next_node]
            route_info.append(f"[0,{self.start_node},{output_interface}]") if i == 0 else None
            route_info.append(f"[{input_interface},{current_node},{output_interface}]") if i > 0 else None
    
        # Para el nodo final, obtener la interfaz de entrada desde el nodo anterior
        final_node = route[-1]
        input_interface_final = self.graphIE[route[-2]][final_node] if len(route) > 1 else "0"
    
        route_info.append(f"[{input_interface_final},{final_node},0]")  # Agregar nodo final
        return ";".join(route_info)

    def run(self):
        old_results = self.result_db.load_results()
        for generation in range(self.generations):
            self.evolve()
            best_route = min(self.population, key=self.fitness)
            self.update_best_routes(best_route)

        final_best_route = min(self.population, key=self.fitness)
        route_with_interfaces = self.print_route_with_interfaces(final_best_route)
        results = {
            'best_route': final_best_route,
            'distance': self.fitness(final_best_route)[0],
            'intermediate_nodes': self.fitness(final_best_route)[1],
            'path': final_best_route,
            'route_with_interfaces': route_with_interfaces
        }

        # Obtener las mejores rutas calculadas
        best_routes = []
        for route in self.best_routes:
            distance, num_intermediate = self.fitness(route)
            route_with_interfaces = self.print_route_with_interfaces(route)
            best_routes.append({
                'distance': distance,
                'intermediate_nodes': num_intermediate,
                'path': route,
                'route_with_interfaces': route_with_interfaces
            })

        # Guardar resultados en JSON
        self.result_db.update_results(self.start_node, self.end_node, best_routes)

        # Comparar resultados
        comparison = self.result_db.compare_results(results, old_results)
        #print(f"\nComparación de resultados: {comparison}")

        #print(f"\nRuta Optima: {route_with_interfaces}")
        result_message = ""

        for route in self.result_db.results[f"{self.start_node}_{self.end_node}"]['best_routes']:
            routes_with_interfaces = route['route_with_interfaces']
            result_message += f"Ruta: {routes_with_interfaces}, Distancia: {route['distance']}\n"
        #print(result_message.strip())
        return final_best_route, result_message.strip() 

def main():
    #Obtenga los argumentos
    sourceNode = int(sys.argv[1])
    destinationNode = int(sys.argv[2])
    msgClass = int(sys.argv[3])

    start_node = "Nodo"+str(sourceNode)
    end_node = "Nodo"+str(destinationNode)
    
    # Preguntar al usuario el tipo de mensaje
    message_type = str(msgClass)
    
    # Establecer parámetros del algoritmo genético según el tipo de mensaje
    if message_type == '1':
        population_size = 15
        generations = 3
    elif message_type == '2':
        population_size = 20
        generations = 3
    elif message_type == '3':
        population_size = 15
        generations = 5
    else:
        print("Tipo de mensaje no válido. Por favor, ingrese 1, 2 o 3.")
        return

    # Inicia la medición del tiempo
    start_time = time.time()
    ga = GeneticAlgorithm(graph, graphIE, graphIS, start_node, end_node, population_size, generations)

    # Cargar resultados previos
    previous_results = ga.result_db.load_results()
    key = f"{start_node}_{end_node}"
    
    # Lógica para ejecutar el algoritmo genético según el tipo de mensaje
    if message_type in ['2', '3']:
        result = ga.run()  # Ejecutar el algoritmo genético
    elif message_type == '1':
        # Verificar si hay resultados guardados
        if key in previous_results and previous_results[key]['best_routes']:
            # Imprimir la mejor ruta guardada
            best_route = previous_results[key]['best_routes'][0]
            result = best_route  # Guardar el resultado para el tiempo de simulación
        else:
            # Si no hay ruta guardada, ejecutar el algoritmo genético
            result = ga.run()

    # Imprimir resultados según el tipo de mensaje
    best_routes = ga.result_db.results.get(key, {}).get('best_routes', [])

    def handle_message_type_1():
        if best_routes:
            best_route = best_routes[0]  # Mejor ruta guardada
            print(f"Ruta Optima: {best_route['route_with_interfaces']}")
        else:
            print(f"Ruta Optima: {result['route_with_interfaces']}")  # Ruta calculada en este intento

    def handle_message_type_2():
        if len(best_routes) > 1:
            second_best_route = best_routes[1]
            print(f"Ruta: {second_best_route['route_with_interfaces']}")
        else:
            # Retornar la mejor ruta si no hay segunda mejor
            if best_routes:
                best_route = best_routes[0]
                print(f"Ruta: {best_route['route_with_interfaces']}")
            else:
                print("No hay suficiente información para mostrar la segunda mejor ruta.")

    def handle_message_type_3():
        if len(best_routes) > 2:
            best_route = best_routes[0]
            third_best_route = best_routes[2]
            print(f"Ruta Optima: {best_route['route_with_interfaces']}")
            print(f"Ruta: {third_best_route['route_with_interfaces']}")
        else:
            # Retornar la mejor ruta si no hay tercera mejor
            if len(best_routes) > 1:
                best_route = best_routes[1]
                print(f"Ruta: {best_route['route_with_interfaces']}")
            elif best_routes:
                best_route = best_routes[0]
                print(f"Ruta: {best_route['route_with_interfaces']}")
            else:
                print("No hay suficiente información para mostrar la tercera mejor ruta.")

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
    print(f"Delay: {simulation_time:.2f}")  # Finaliza la medición del tiempo

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"Ocurrió un error: {e}")
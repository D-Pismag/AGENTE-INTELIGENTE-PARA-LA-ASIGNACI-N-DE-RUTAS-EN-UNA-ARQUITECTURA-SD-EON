clear; clc; close all;

% ==============================
% ESCENARIO COMPARATIVO
% ==============================

RecursoEspectral = [1000, 1025, 1050, 1075, 1100, 1125, 1150, 1175, 1200, 1225, 1250, 1275, 1300, 1325, 1350, 1375, 1400, 1425, 1450, 1475, 1500]; % Valores de recurso espectral disponible

%% Gráfica Throughput

% Throughput

% 4 JF
throughput_AI_1  = [1.588, 1.617, 1.645, 1.674, 1.702, 1.729, 1.756, 1.782, 1.812, 1.847, 1.882, 1.918, 1.952, 1.987, 2.021, 2.054, 2.086, 2.119, 2.150, 2.179, 2.207];
throughput_Dij_1  = [1.591, 1.620, 1.648, 1.677, 1.704, 1.731, 1.759, 1.785, 1.816, 1.851, 1.886, 1.922, 1.957, 1.992, 2.025, 2.059, 2.092, 2.123, 2.154, 2.183, 2.211];
% 4.5 JF
throughput_AI_2  = [1.737, 1.767, 1.796, 1.836, 1.876, 1.916, 1.955, 1.995, 2.033, 2.070, 2.106, 2.142, 2.176, 2.207, 2.232, 2.253, 2.270, 2.287, 2.311, 2.350, 2.391];
throughput_Dij_2  = [1.740, 1.770, 1.800, 1.840, 1.881, 1.921, 1.959, 1.999, 2.037, 2.074, 2.111, 2.145, 2.179, 2.211, 2.234, 2.253, 2.271, 2.288, 2.317, 2.356, 2.396];
% 5 JF
throughput_AI_3  = [1.904, 1.948, 1.991, 2.035, 2.076, 2.117, 2.155, 2.192, 2.224, 2.247, 2.268, 2.287, 2.316, 2.360, 2.404, 2.448, 2.492, 2.495, 2.497, 2.495, 2.497];
throughput_Dij_3  = [1.908, 1.952, 1.995, 2.038, 2.080, 2.121, 2.159, 2.195, 2.226, 2.249, 2.268, 2.288, 2.321, 2.364, 2.409, 2.453, 2.493, 2.494, 2.493, 2.492, 2.493];
figure(1);

% Trazar las curvas con diferentes estilos
plot(RecursoEspectral, throughput_AI_3, '-rs', 'LineWidth', 2);
hold on;
plot(RecursoEspectral, throughput_AI_2, '-bs', 'LineWidth', 2);
plot(RecursoEspectral, throughput_AI_1, '-gs', 'LineWidth', 2);
plot(RecursoEspectral, throughput_Dij_3, '--r^', 'LineWidth', 2);
plot(RecursoEspectral, throughput_Dij_2, '--b^', 'LineWidth', 2);
plot(RecursoEspectral, throughput_Dij_1, '--g^', 'LineWidth', 2);
hold off;

% Etiquetas
title('Throughput de recepción', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Throughput [Gbps]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend({'AI - 5 JF', 'AI - 4.5 JF', 'AI - 4 JF', ...
        'Dijkstra - 5 JF', 'Dijkstra - 4.5 JF', 'Dijkstra - 4 JF'}, ...
       'NumColumns', 2, 'Location', 'best', 'FontSize', 18);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([1190 1310]);        % Rango del eje X
ylim([1.5 2.6]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 24);

%% Probabilidad de bloqueo

% Probabilidades de bloqueo

% 4 JF
solicitudesBloqueadas_AI_1 = [24.249, 22.450, 20.729, 19.031, 17.295, 15.653, 14.068, 12.434, 11.176, 11.030, 10.871, 10.685, 10.479, 10.224, 9.974, 9.670, 9.346, 8.987, 8.478, 7.948, 7.274];
solicitudesBloqueadas_Dij_1 = [23.944, 22.243, 20.512, 18.759, 17.084, 15.364, 13.795, 12.058, 11.131, 10.969, 10.810, 10.623, 10.397, 10.179, 9.911, 9.603, 9.270, 8.866, 8.391, 7.777, 7.102];
% 4.5 JF
solicitudesBloqueadas_AI_2 = [15.408, 13.489, 11.709, 11.305, 11.107, 10.897, 10.663, 10.401, 10.108, 9.725, 9.329, 8.838, 8.236, 7.498, 6.093, 4.382, 2.629, 1.071, 0.496, 0.140, 0.000];
solicitudesBloqueadas_Dij_2 = [15.053, 13.261, 11.488, 11.240, 11.033, 10.840, 10.600, 10.309, 10.001, 9.649, 9.206, 8.698, 8.073, 7.314, 5.721, 3.984, 2.335, 0.827, 0.000, 0.000, 0.000];
% 5 JF
solicitudesBloqueadas_AI_3 = [10.980, 10.727, 10.415, 10.083, 9.707, 9.189, 8.605, 7.911, 6.715, 4.743, 2.826, 1.087, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000];
solicitudesBloqueadas_Dij_3 = [10.903, 10.654, 10.361, 10.004, 9.575, 9.086, 8.467, 7.713, 6.416, 4.447, 2.518, 0.829, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000];

figure(2);
% Trazar las curvas con diferentes estilos
plot(RecursoEspectral, solicitudesBloqueadas_AI_3, '-rs', 'LineWidth', 2);
hold on;
plot(RecursoEspectral, solicitudesBloqueadas_AI_2, '-bs', 'LineWidth', 2);
plot(RecursoEspectral, solicitudesBloqueadas_AI_1, '-gs', 'LineWidth', 2);
plot(RecursoEspectral, solicitudesBloqueadas_Dij_3, '--r^', 'LineWidth', 2);
plot(RecursoEspectral, solicitudesBloqueadas_Dij_2, '--b^', 'LineWidth', 2);
plot(RecursoEspectral, solicitudesBloqueadas_Dij_1, '--g^', 'LineWidth', 2);
hold off;

% Etiquetas
title('Probabilidad de bloqueo', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Pr_B [%]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend({'AI - 5 JF', 'AI - 4.5 JF', 'AI - 4 JF', ...
        'Dijkstra - 5 JF', 'Dijkstra - 4.5 JF', 'Dijkstra - 4 JF'}, ...
       'NumColumns', 2, 'Location', 'best', 'FontSize', 18);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([0 4]);        % Rango del eje X
%ylim([0 16]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 24);

%% Gráfica retardos E2E

% Delay E2E

% 4 JF
t_delayE2E_AI_C1_1 = [52.031, 51.946, 51.913, 51.983, 51.952, 51.876, 51.885, 51.750, 52.044, 51.856, 51.992, 51.947, 52.001, 51.981, 52.015, 52.101, 52.118, 51.953, 52.230, 52.266, 52.454];
t_delayE2E_AI_C2_1 = [167.994, 165.799, 163.255, 160.536, 157.550, 154.333, 150.449, 145.841, 139.751, 132.964, 126.573, 119.688, 113.400, 107.343, 101.337, 95.619, 90.050, 84.832, 79.983, 75.383, 71.304];
t_delayE2E_AI_C3_1 = [186.505, 182.244, 177.771, 173.046, 167.615, 161.561, 155.316, 147.958, 140.048, 133.301, 126.832, 119.961, 113.692, 107.655, 101.551, 95.920, 90.323, 85.109, 80.299, 75.715, 71.595];
t_delayE2E_Dij_C1_1 = [51.514, 51.589, 51.582, 51.581, 51.490, 51.485, 51.498, 51.547, 51.410, 51.506, 51.504, 51.538, 51.568, 51.624, 51.644, 51.719, 51.783, 51.854, 51.942, 52.097, 52.211];
t_delayE2E_Dij_C2_1 = [167.315, 165.371, 162.526, 159.770, 156.655, 153.385, 149.506, 144.309, 138.148, 131.516, 124.970, 118.386, 112.060, 106.121, 100.086, 94.430, 88.942, 83.732, 78.894, 74.361, 70.196];
t_delayE2E_Dij_C3_1 = [185.597, 181.575, 176.974, 171.930, 166.556, 160.268, 153.892, 145.663, 138.422, 131.807, 125.214, 118.780, 112.394, 106.433, 100.372, 94.670, 89.187, 84.032, 79.199, 74.695, 70.496];
% 4.5 JF
t_delayE2E_AI_C1_2 = [52.319, 52.590, 52.376, 52.331, 52.275, 52.399, 52.420, 52.604, 52.547, 52.542, 52.512, 52.684, 52.746, 52.828, 55.019, 56.039, 56.699, 54.705, 49.165, 41.441, 33.697];
t_delayE2E_AI_C2_2 = [153.698, 148.728, 142.926, 135.229, 127.867, 120.381, 113.277, 106.354, 99.740, 93.197, 87.272, 81.496, 76.258, 71.510, 67.920, 64.739, 60.000, 54.299, 46.457, 38.750, 31.026];
t_delayE2E_AI_C3_2 = [160.259, 152.210, 143.472, 135.666, 128.147, 120.702, 113.667, 106.647, 100.029, 93.569, 87.618, 81.850, 76.627, 71.873, 68.285, 65.079, 60.328, 54.639, 46.804, 39.090, 31.374];
t_delayE2E_Dij_C1_2 = [52.020, 51.927, 51.920, 52.016, 52.079, 51.821, 51.949, 52.105, 52.148, 52.137, 52.142, 52.346, 52.342, 52.449, 56.578, 56.149, 55.922, 53.886, 47.758, 39.675, 32.064];
t_delayE2E_Dij_C2_2 = [152.618, 147.755, 141.614, 133.948, 126.577, 118.846, 111.895, 104.973, 98.585, 91.882, 85.909, 80.523, 75.274, 70.554, 66.967, 63.306, 58.746, 52.997, 45.047, 36.977, 29.374];
t_delayE2E_Dij_C3_2 = [158.734, 151.016, 142.069, 134.393, 126.951, 119.164, 112.187, 105.314, 98.920, 92.236, 86.224, 80.824, 75.630, 70.936, 67.316, 63.668, 59.123, 53.326, 45.394, 37.329, 29.721];
% 5 JF
t_delayE2E_AI_C1_3 = [52.847, 52.898, 53.149, 53.030, 53.024, 53.082, 53.071, 53.359, 56.059, 57.186, 57.384, 55.322, 48.806, 40.358, 31.954, 22.800, 14.418, 13.693, 13.695, 13.685, 13.685];
t_delayE2E_AI_C2_3 = [123.026, 114.778, 107.262, 99.815, 92.803, 85.873, 79.448, 74.070, 69.240, 65.561, 60.818, 54.597, 45.767, 37.351, 28.963, 19.837, 11.475, 10.746, 10.741, 10.741, 10.739];
t_delayE2E_AI_C3_3 = [123.393, 115.188, 107.652, 100.185, 93.206, 86.265, 79.839, 74.455, 69.662, 65.968, 61.227, 55.004, 46.155, 37.758, 29.371, 20.240, 11.870, 11.145, 11.141, 11.140, 11.138];
t_delayE2E_Dij_C1_3 = [52.588, 52.513, 52.672, 52.632, 52.636, 52.539, 52.622, 52.859, 55.162, 56.178, 56.343, 54.468, 47.382, 38.857, 29.992, 20.979, 13.721, 13.668, 13.661, 13.668, 13.662];
t_delayE2E_Dij_C2_3 = [121.451, 113.523, 105.816, 98.154, 91.363, 84.469, 78.467, 72.853, 68.376, 64.587, 59.433, 53.232, 44.340, 35.827, 26.974, 18.001, 10.765, 10.704, 10.706, 10.704, 10.703];
t_delayE2E_Dij_C3_3 = [121.886, 113.950, 106.221, 98.563, 91.760, 84.886, 78.912, 73.309, 68.826, 64.991, 59.853, 53.657, 44.761, 36.242, 27.395, 18.411, 11.172, 11.114, 11.109, 11.112, 11.109];

figure(3); % 4 JF

plot(RecursoEspectral, t_delayE2E_AI_C1_1, '-rs', 'LineWidth', 2);
hold on;
plot(RecursoEspectral, t_delayE2E_AI_C2_1, '-bs', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_AI_C3_1, '-gs', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_Dij_C1_1, '--r^', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_Dij_C2_1, '--b^', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_Dij_C3_1, '--g^', 'LineWidth', 2);

% Etiquetas
title('Retardos E2E - 4 JF', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Retardo [ms]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend({'AI - Paquetes clase 1', 'AI - Paquetes clase 2', 'AI - Paquetes clase 3', ...
        'Dijkstra - Paquetes clase 1', 'Dijkstra - Paquetes clase 2', 'Dijkstra - Paquetes clase 3'}, ...
       'NumColumns', 2, 'Location', 'best', 'FontSize', 18);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([0 4]);        % Rango del eje X
ylim([0 190]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 24);

figure(4); % 4.5 JF

plot(RecursoEspectral, t_delayE2E_AI_C1_2, '-rs', 'LineWidth', 2);
hold on;
plot(RecursoEspectral, t_delayE2E_AI_C2_2, '-bs', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_AI_C3_2, '-gs', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_Dij_C1_2, '--r^', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_Dij_C2_2, '--b^', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_Dij_C3_2, '--g^', 'LineWidth', 2);

% Etiquetas
title('Retardos E2E - 4.5 JF', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Retardo [ms]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend({'AI - Paquetes clase 1', 'AI - Paquetes clase 2', 'AI - Paquetes clase 3', ...
        'Dijkstra - Paquetes clase 1', 'Dijkstra - Paquetes clase 2', 'Dijkstra - Paquetes clase 3'}, ...
       'NumColumns', 2, 'Location', 'best', 'FontSize', 18);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([0 4]);        % Rango del eje X
ylim([0 190]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 24);

figure(5); % 5 JF

plot(RecursoEspectral, t_delayE2E_AI_C1_3, '-rs', 'LineWidth', 2);
hold on;
plot(RecursoEspectral, t_delayE2E_AI_C2_3, '-bs', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_AI_C3_3, '-gs', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_Dij_C1_3, '--r^', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_Dij_C2_3, '--b^', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_Dij_C3_3, '--g^', 'LineWidth', 2);

% Etiquetas
title('Retardos E2E - 5 JF', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Retardo [ms]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend({'AI - Paquetes clase 1', 'AI - Paquetes clase 2', 'AI - Paquetes clase 3', ...
        'Dijkstra - Paquetes clase 1', 'Dijkstra - Paquetes clase 2', 'Dijkstra - Paquetes clase 3'}, ...
       'NumColumns', 2, 'Location', 'best', 'FontSize', 18);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([0 4]);        % Rango del eje X
ylim([0 190]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 24);
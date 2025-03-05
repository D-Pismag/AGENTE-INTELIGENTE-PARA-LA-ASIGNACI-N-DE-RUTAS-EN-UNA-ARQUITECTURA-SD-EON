clear; clc; close all;

% ==============================
% ESCENARIO DE CALIBRACIÓN
% ==============================

JF = [0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4]; % Valores de Jumbo Frames considerados

%% Gráfica Throughput

% Throughput

% 1.25 Gbps
throughput_in_1  = [0.117, 0.318, 0.699, 1.012, 1.241, 1.243, 1.243, 1.242, 1.243];
% 2 Gbps
throughput_in_2  = [0.118, 0.319, 0.754, 1.086, 1.367, 1.663, 1.984, 1.986, 1.988];
% 2.5 Gbps
throughput_in_3  = [0.118, 0.319, 0.760, 1.139, 1.398, 1.732, 2.020, 2.322, 2.485];

figure(1);
% Trazar las curvas con diferentes estilos
plot(JF, throughput_in_3, '-rs', 'LineWidth', 2, 'DisplayName', 'R = 2.5 Gbps');
hold on;
plot(JF, throughput_in_2, '-bs', 'LineWidth', 2, 'DisplayName', 'R = 2 Gbps');
plot(JF, throughput_in_1, '-gs', 'LineWidth', 2, 'DisplayName', 'R = 1.25 Gbps');
hold off;

% Etiquetas
title('Throughput de recepción', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Capacidad del buffer [JF]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Throughput [Gbps]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
xlim([0 4]);        % Rango del eje X
ylim([0 2.6]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);

%% Probabilidad de bloqueo

% Probabilidades de bloqueo

% 1.25 Gbps
solicitudesBloqueadas_1 = [79.917, 48.485, 18.845, 1.919, 0.000, 0.000, 0.000, 0.000, 0.000];
% 2 Gbps
solicitudesBloqueadas_2 = [87.398, 67.768, 43.923, 21.526, 7.683, 0.002, 0.000, 0.000, 0.000];
% 2.5 Gbps
solicitudesBloqueadas_3 = [89.916, 74.177, 56.866, 37.203, 18.339, 7.878, 1.898, 0.000, 0.000];

figure(2);
% Trazar las curvas con diferentes estilos
plot(JF, solicitudesBloqueadas_3, '-rs', 'LineWidth', 2, 'DisplayName', 'R = 2.5 Gbps');
hold on;
plot(JF, solicitudesBloqueadas_2, '-bs', 'LineWidth', 2, 'DisplayName', 'R = 2 Gbps');
plot(JF, solicitudesBloqueadas_1, '-gs', 'LineWidth', 2, 'DisplayName', 'R = 1.25 Gbps');
hold off;

% Etiquetas
title('Probabilidad de bloqueo', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Capacidad del buffer [JF]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Pr_B [%]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
xlim([0 4]);        % Rango del eje X
ylim([-5 100]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);

%% Gráfica retardos E2E

% Delay E2E

% 1.25 Gbps
t_delayE2E_C1_1 = [204.519, 55.024, 55.848, 56.479, 12.835, 13.567, 14.425, 15.315, 16.213];
t_delayE2E_C2_1 = [203.880, 194.872, 116.546, 56.060, 10.458, 10.692, 10.947, 11.207, 11.462];
t_delayE2E_C3_1 = [204.469, 195.785, 124.868, 56.335, 10.701, 11.052, 11.424, 11.682, 12.060];
t_EstablecimientoRecursosNodo_1 = [182.888, 173.291, 114.736, 53.449, 7.591, 7.572, 7.572, 7.573, 7.575];
% 2 Gbps
t_delayE2E_C1_2 = [194.306, 54.787, 55.313, 55.773, 56.385, 51.683, 12.660, 13.156, 13.706];
t_delayE2E_C2_2 = [194.336, 202.690, 109.906, 117.789, 89.413, 49.758, 10.469, 10.581, 10.737];
t_delayE2E_C3_2 = [194.000, 203.727, 172.444, 130.016, 89.596, 49.965, 10.772, 10.885, 11.112];
t_EstablecimientoRecursosNodo_2 = [177.777, 183.304, 146.109, 117.788, 84.512, 47.231, 7.620, 7.576, 7.571];
% 2.5 Gbps
t_delayE2E_C1_3 = [187.985, 54.897, 55.020, 55.499, 55.891, 56.122, 56.730, 28.192, 12.888];
t_delayE2E_C2_3 = [186.833, 200.050, 109.070, 115.423, 116.241, 87.872, 56.092, 26.075, 10.515];
t_delayE2E_C3_3 = [187.842, 200.385, 187.811, 154.783, 124.084, 88.106, 56.382, 26.313, 10.813];
t_EstablecimientoRecursosNodo_3 = [173.994, 181.901, 157.818, 132.661, 114.264, 82.933, 53.457, 23.347, 7.586];

figure(3);

% 1.25 Gbps
plot(JF, t_delayE2E_C1_1, '-rs', 'LineWidth', 2, 'DisplayName', 'Paquetes clase 1');
hold on;
plot(JF, t_delayE2E_C2_1, '-bs', 'LineWidth', 2, 'DisplayName', 'Paquetes clase 2');
plot(JF, t_delayE2E_C3_1, '-gs', 'LineWidth', 2, 'DisplayName', 'Paquetes clase 3');
%plot(JF, t_EstablecimientoRecursosNodo_1, ':ks', 'LineWidth', 2, 'DisplayName', 'Establecimiento de recursos');
hold off;

% Etiquetas
title('Retardos E2E - 1.25 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Capacidad del buffer [JF]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Retardo [ms]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
xlim([0 4]);        % Rango del eje X
ylim([0 210]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);

figure(4);

% 2 Gbps
plot(JF, t_delayE2E_C1_2, '-rs', 'LineWidth', 2, 'DisplayName', 'Paquetes clase 1');
hold on;
plot(JF, t_delayE2E_C2_2, '-bs', 'LineWidth', 2, 'DisplayName', 'Paquetes clase 2');
plot(JF, t_delayE2E_C3_2, '-gs', 'LineWidth', 2, 'DisplayName', 'Paquetes clase 3');
%plot(JF, t_EstablecimientoRecursosNodo_2, ':ks', 'LineWidth', 2, 'DisplayName', 'Establecimiento de recursos');
hold off;

% Etiquetas
title('Retardos E2E - 2 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Capacidad del buffer [JF]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Retardo [ms]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
xlim([0 4]);        % Rango del eje X
ylim([0 210]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);

figure(5);

% 1.25 Gbps
plot(JF, t_delayE2E_C1_3, '-rs', 'LineWidth', 2, 'DisplayName', 'Paquetes clase 1');
hold on;
plot(JF, t_delayE2E_C2_3, '-bs', 'LineWidth', 2, 'DisplayName', 'Paquetes clase 2');
plot(JF, t_delayE2E_C3_3, '-gs', 'LineWidth', 2, 'DisplayName', 'Paquetes clase 3');
%plot(JF, t_EstablecimientoRecursosNodo_3, ':ks', 'LineWidth', 2, 'DisplayName', 'Establecimiento de recursos');
hold off;

% Etiquetas
title('Retardos E2E - 2.5 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Capacidad del buffer [JF]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Retardo [ms]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
xlim([0 4]);        % Rango del eje X
ylim([0 210]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);

%% Solicitudes en el controlador

% 1.25 Gbps
SolicitudesControladorR_1 = [1078931, 418826, 189316, 122541, 93877, 74205, 61137, 52935, 45920];
SolicitudesControladorP_1 = [539943, 209933, 132918, 109720, 93877, 74205, 61137, 52935, 45920];
% 2 Gbps

% 2.5 Gbps

figure(6); % 1.25 Gbps

a = bar(JF,SolicitudesControladorR_1, 'grouped', 'FaceColor', [0.8500 0.3250 0.0980] ,'DisplayName', 'Solicitudes recibidas');
hold on;
b = bar(JF,SolicitudesControladorP_1, 'grouped', 'FaceColor', [0.3010 0.7450 0.9330] ,'DisplayName', 'Solicitudes procesadas');

a.YData;
b.YData;
    
% Etiquetas
title('Solicitudes de recursos - 1.25 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Capacidad del buffer [JF]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Cantidad de solicitudes', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
xlim([-0.4 4.4]);        % Rango del eje X
ylim([0 12e5]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);
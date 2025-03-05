clear; clc; close all;

% ==============================
% ESCENARIO DE CALIBRACIÓN
% ==============================

Generaciones = [1, 2, 3, 5, 7, 10, 15, 20, 25, 30, 35, 40, 45, 50]; % Valores de Jumbo Frames considerados

%% Gráfica Distancia

% Distancia

% Poblacion Inicial 1
Poblacion_In_1  = [13680, 13470, 13140, 13290, 13320, 12390, 11340, 12690, 15000, 13350, 13020, 10980, 11100, 13170];
% Poblacion Inicial 5
Poblacion_In_5 = [10260, 9690, 8910, 9150, 8400, 9000, 9150, 8280, 8550, 7650, 9090, 8520, 8100, 8520];
% Poblacion Inicial 10
Poblacion_In_10  = [8220, 8040, 8100, 7470, 8310, 8190, 8070, 7770, 7590, 7620, 7410, 7890, 7560, 7770];
% Poblacion Inicial 15
Poblacion_In_15  = [8640, 8310, 8280, 7530, 8070, 7830, 7770, 7290, 7260, 7230, 7440, 7470, 7620, 7410];
% Poblacion Inicial 20
Poblacion_In_20  = [7920, 7470, 7470, 7650, 7620, 7230, 7200, 7200, 7230, 7200, 7200, 7230, 7260, 7200];
% Poblacion Inicial 25
Poblacion_In_25 = [7500, 7260, 7320, 7200, 7260, 7410, 7230, 7230, 7410, 7200, 7200, 7410, 7200, 7200];
% Poblacion Inicial 30
Poblacion_In_30 = [7290, 7200, 7230, 7200, 7200, 7410, 7200, 7200, 7200, 7200, 7230, 7200, 7200, 7200];

figure(1);
% Trazar las curvas con diferentes estilos
plot(Generaciones, Poblacion_In_1, '-rs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 1');
hold on;
plot(Generaciones, Poblacion_In_5, '-bs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 5');
plot(Generaciones, Poblacion_In_10, '-gs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 10');
plot(Generaciones, Poblacion_In_15, '-ys', 'LineWidth', 2, 'DisplayName', 'Poblacion = 15');
plot(Generaciones, Poblacion_In_20, '-cs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 20');
plot(Generaciones, Poblacion_In_25, '-ms', 'LineWidth', 2, 'DisplayName', 'Poblacion = 25');
plot(Generaciones, Poblacion_In_30, '-ks', 'LineWidth', 2, 'DisplayName', 'Poblacion = 30');
hold off;

% Etiquetas
title('Costo de la ruta generada', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Numero de Generaciones', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Costo [Und.]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 18);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
xlim([0 50]);        % Rango del eje X
ylim([7000 15500]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 24);

%% Grafica Nodos Intermedios

% Nodos Intermedios

% Nodos Intermedios 1
Nodos_In_1 = [5.8, 5.9, 5.3, 5.6, 5.7, 4.9, 4.7, 5.1, 6.6, 5.9, 5.8, 4.8, 4.6, 5.2];
% Nodos Intermedios 5
Nodos_In_5 = [4.1, 3.3, 3.7, 3.3, 3.7, 3.9, 3.1, 3.5, 3.7, 3.2, 3.8, 3.2, 3.4, 2.9];
% Nodos Intermedios 10
Nodos_In_10 = [3.6, 3.1, 3.2, 3.1, 3.5, 3.2, 3.4, 3, 2.9, 3.2, 3.1, 3.3, 3.1, 3];
% Nodos Intermedios 15
Nodos_In_15 = [3.2, 3.5, 3.5, 3.1, 3.4, 3.3, 3.5, 3, 3, 3, 3.1, 3.1, 3.2, 3.1];
% Nodos Intermedios 20
Nodos_In_20 = [3.1, 3.1, 3.1, 3.2, 3.2, 3, 3, 3, 3, 3, 3, 3, 3, 3];
% Nodos Intermedios 25
Nodos_In_25 = [3.1, 3, 3, 3, 3, 3.1, 3, 3, 3.1, 3, 3, 3.1, 3, 3];
% Nodos Intermedios 30
Nodos_In_30 = [3, 3, 3, 3, 3, 3.1, 3, 3, 3, 3, 3, 3, 3, 3];


figure(2);
% Trazar las curvas con diferentes estilos
plot(Generaciones,Nodos_In_1, '-rs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 1');
hold on;
plot(Generaciones, Nodos_In_5, '-bs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 5');
plot(Generaciones, Nodos_In_10, '-gs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 10');
plot(Generaciones, Nodos_In_15, '-ys', 'LineWidth', 2, 'DisplayName', 'Poblacion = 15');
plot(Generaciones, Nodos_In_20, '-cs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 20');
plot(Generaciones, Nodos_In_25, '-ms', 'LineWidth', 2, 'DisplayName', 'Poblacion = 25');
plot(Generaciones, Nodos_In_30, '-ks', 'LineWidth', 2, 'DisplayName', 'Poblacion = 30');

hold off;

% Etiquetas
title('Nodos Intermedios Promedio', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Numero de Generaciones', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Nodos [U]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 18);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
xlim([0 50]);        % Rango del eje X
ylim([0 8]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 24);

%% Grafica de Tiempo

%Tiempo promedio

%Tiempo promedio 1
Tiempo_In_1 = [1.662, 1.695, 1.194, 1.3, 1.696, 1.398, 1.697, 1.892, 2.101, 1.996, 2.002, 2.294, 2.185, 2.288];
%Tiempo promedio 5
Tiempo_In_5 = [1.796, 2.399, 2.291, 2.511, 3.698, 4.581, 5.75, 7.197, 8.888, 10.588, 11.593, 13.594, 14.607, 15.201];
%Tiempo promedio 10
Tiempo_In_10 = [2.8, 3.793, 4.891, 7.396, 9.185, 12.106, 16.189, 26.092, 28.505, 33.058, 37.485, 44.252, 44.782, 53.689];
%Tiempo promedio 15
Tiempo_In_15 = [4.294, 6.998, 8.803, 14.09, 17.106, 25.156, 34.597, 49.394, 55.794, 61.301, 83.087, 89.362, 97.296, 103.897];
%Tiempo promedio 20
Tiempo_In_20 = [5.658, 9.686, 13.255, 18.7, 32.469, 41.821, 58.261, 81.274, 102.749, 117.729, 148.815, 178.591, 179.114, 219.551];
%Tiempo promedio 25
Tiempo_In_25 = [8.786, 14.221, 21.662, 34.774, 45.557, 63.094, 95.748, 124.118, 152.352, 188.2, 211.171, 264.096, 290.865, 297.509];
%Tiempo promedio 30
Tiempo_In_30 = [11.204, 20.965, 32.426, 44.552, 65.688, 90.934, 128.994, 176.815, 225.979, 265.444, 304.702, 362.551, 385.654, 427.502];


figure(3);
% Trazar las curvas con diferentes estilos
plot(Generaciones,Tiempo_In_1, '-rs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 1');
hold on;
plot(Generaciones, Tiempo_In_5, '-bs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 5');
plot(Generaciones, Tiempo_In_10, '-gs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 10');
plot(Generaciones, Tiempo_In_15, '-ys', 'LineWidth', 2, 'DisplayName', 'Poblacion = 15');
plot(Generaciones, Tiempo_In_20, '-cs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 20');
plot(Generaciones, Tiempo_In_25, '-ms', 'LineWidth', 2, 'DisplayName', 'Poblacion = 25');
plot(Generaciones, Tiempo_In_30, '-ks', 'LineWidth', 2, 'DisplayName', 'Poblacion = 30');
hold off;

% Etiquetas
title('Retardo de ejecución del agente inteligente', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Numero de Generaciones', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Tiempo [ms]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 18);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
xlim([0 50]);    % Rango del eje X
%ylim([0 30]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 24);

%% Grafico de porcentaje de ruta optima

% Porcentaje Ruta Optima

%Ruta Optima 1
RutaOp_In_1 = [0, 0, 0, 0, 0, 0.2, 0, 0.1, 0, 0, 0, 0.1, 0, 0.1];
%Ruta Optima 5
RutaOp_In_5 = [0.2, 0.2, 0.1, 0.2, 0.2, 0.1, 0.3, 0.4, 0.3, 0.7, 0, 0.4, 0.4, 0.5];
%Ruta Optima 10
RutaOp_In_10 = [0.3, 0.3, 0.5, 0.7, 0.3, 0.4, 0.5, 0.6, 0.6, 0.8, 0.9, 0.5, 0.4, 0.6];
%Ruta Optima 15
RutaOp_In_15 = [0.4, 0.3, 0.4, 0.5, 0.5, 0.7, 0.5, 0.7, 0.8, 0.9, 0.8, 0.7, 0.8, 0.9];
%Ruta Optima 20
RutaOp_In_20 = [0.2, 0.7, 0.7, 0.7, 0.8, 0.9, 1, 1, 0.9, 1, 1, 0.9, 0.8, 1];
%Ruta Optima 25
RutaOp_In_25 = [0.6, 0.7, 0.6, 1, 0.8, 1, 0.9, 0.9, 0.9, 1, 1, 0.9, 1, 1];
%Ruta Optima 30
RutaOp_In_30 = [0.7, 1, 0.9, 1, 1, 0.9, 1, 1, 1, 1, 0.9, 1, 1, 1];

figure(4);
% Trazar las curvas con diferentes estilos
plot(Generaciones, 100*RutaOp_In_1, '-rs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 1');
hold on;
plot(Generaciones, 100*RutaOp_In_5, '-bs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 5');
plot(Generaciones, 100*RutaOp_In_10, '-gs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 10');
plot(Generaciones, 100*RutaOp_In_15, '-ys', 'LineWidth', 2, 'DisplayName', 'Poblacion = 15');
plot(Generaciones, 100*RutaOp_In_20, '-cs', 'LineWidth', 2, 'DisplayName', 'Poblacion = 20');
plot(Generaciones, 100*RutaOp_In_25, '-ms', 'LineWidth', 2, 'DisplayName', 'Poblacion = 25');
plot(Generaciones, 100*RutaOp_In_30, '-ks', 'LineWidth', 2, 'DisplayName', 'Poblacion = 30');
hold off;

% Etiquetas
title('Probabilidad del agente de generar una ruta óptima', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Numero de Generaciones', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Pr_{RO} [%]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 18);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
xlim([0 50]);    % Rango del eje X
ylim([0 100]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 24);
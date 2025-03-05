clear; clc; close all;

% ==============================
% ESCENARIO DE RECURSOS LIMITADOS - 1.25 Gbps
% ==============================

RecursoEspectral = [1200, 1220, 1240, 1260, 1280, 1300]; % Valores de Jumbo Frames considerados

%% Gráfica Throughput

% Throughput

% 2 JF
throughput_in_1  = [0.891, 0.902, 0.916, 0.931, 0.945, 0.959];
% 2.5 JF
throughput_in_2  = [1.100, 1.112, 1.122, 1.130, 1.138, 1.145];
% 3 JF
throughput_in_3  = [1.248, 1.248, 1.248, 1.248, 1.248, 1.247];

figure(1);
% Trazar las curvas con diferentes estilos
plot(RecursoEspectral, throughput_in_3, '-rs', 'LineWidth', 2, 'DisplayName', '3 JF');
hold on;
plot(RecursoEspectral, throughput_in_2, '-bs', 'LineWidth', 2, 'DisplayName', '2.5 JF');
plot(RecursoEspectral, throughput_in_1, '-gs', 'LineWidth', 2, 'DisplayName', '2 JF');
hold off;

% Etiquetas
title('Throughput de recepción - 1.25 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Throughput [Gbps]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([1190 1310]);        % Rango del eje X
ylim([0.8 1.30]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);

%% Probabilidad de bloqueo

% Probabilidades de bloqueo

% 2 JF
solicitudesBloqueadas_1 = [12.033, 11.012, 10.882, 10.772, 10.647, 10.491];
% 2.5 JF
solicitudesBloqueadas_2 = [7.650, 6.592, 5.040, 3.549, 2.167, 0.722];
% 3 JF
solicitudesBloqueadas_3 = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000];

figure(2);
% Trazar las curvas con diferentes estilos
plot(RecursoEspectral, solicitudesBloqueadas_3, '-rs', 'LineWidth', 2, 'DisplayName', '3 JF');
hold on;
plot(RecursoEspectral, solicitudesBloqueadas_2, '-bs', 'LineWidth', 2, 'DisplayName', '2.5 JF');
plot(RecursoEspectral, solicitudesBloqueadas_1, '-gs', 'LineWidth', 2, 'DisplayName', '2 JF');
hold off;

% Etiquetas
title('Probabilidad de bloqueo - 1.25 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Pr_B [%]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([0 4]);        % Rango del eje X
ylim([0 16]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);

%% Gráfica retardos E2E

% Delay E2E

% 2.5 Gbps
% 4 JF
t_delayE2E_C1_1 = [52.113, 52.126, 51.952, 52.135, 52.046, 52.137];
t_delayE2E_C2_1 = [145.065, 140.451, 135.259, 129.666, 124.488, 119.398];
t_delayE2E_C3_1 = [146.982, 140.635, 135.459, 129.962, 124.656, 119.693];
% 4.5 JF
t_delayE2E_C1_2 = [53.388, 55.769, 57.321, 56.964, 56.371, 54.137];
t_delayE2E_C2_2 = [72.577, 69.094, 66.076, 62.815, 58.533, 52.785];
t_delayE2E_C3_2 = [72.972, 69.477, 66.449, 63.174, 58.902, 53.079];
% 5 JF
t_delayE2E_C1_3 = [14.444, 14.440, 14.432, 14.442, 14.442, 14.441];
t_delayE2E_C2_3 = [10.936, 10.931, 10.928, 10.927, 10.929, 10.930];
t_delayE2E_C3_3 = [11.394, 11.393, 11.392, 11.387, 11.389, 11.390];

figure(3);

% 4 JF (Círculo)
plot(RecursoEspectral, t_delayE2E_C1_1, '-go', 'LineWidth', 2, 'DisplayName', '');
hold on;
plot(RecursoEspectral, t_delayE2E_C2_1, '-.g^', 'LineWidth', 2, 'DisplayName', '');
plot(RecursoEspectral, t_delayE2E_C3_1, '--gs', 'LineWidth', 2, 'DisplayName', '');

% 4.5 JF (Triángulo)
plot(RecursoEspectral, t_delayE2E_C1_2, '-bo', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_C2_2, '-.b^', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_C3_2, '--bs', 'LineWidth', 2);

% 5 JF (Cuadrado)
plot(RecursoEspectral, t_delayE2E_C1_3, '-ro', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_C2_3, '-.r^', 'LineWidth', 2);
plot(RecursoEspectral, t_delayE2E_C3_3, '--rs', 'LineWidth', 2);

% Etiquetas
title('Retardos E2E - 1.25 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Retardo [ms]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend({'2 JF - Paquetes clase 1', '2 JF - Paquetes clase 2', '2 JF - Paquetes clase 3', ...
        '2.5 JF - Paquetes clase 1', '2.5 JF - Paquetes clase 2', '2.5 JF - Paquetes clase 3', ...
        '3 JF - Paquetes clase 1', '3 JF - Paquetes clase 2', '3 JF - Paquetes clase 3'}, ...
       'NumColumns', 3, 'Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([0 4]);        % Rango del eje X
ylim([0 185]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);
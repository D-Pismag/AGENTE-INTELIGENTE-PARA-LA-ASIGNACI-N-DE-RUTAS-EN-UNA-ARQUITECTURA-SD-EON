clear; clc; close all;

% ==============================
% ESCENARIO DE RECURSOS LIMITADOS - 2.5 Gbps
% ==============================

RecursoEspectral = [1200, 1220, 1240, 1260, 1280, 1300]; % Valores de Jumbo Frames considerados

%% Gráfica Throughput

% Throughput

% 4 JF
throughput_in_1  = [1.811, 1.840, 1.868, 1.896, 1.924, 1.952];
% 4.5 JF
throughput_in_2  = [2.032, 2.062, 2.092, 2.121, 2.148, 2.176];
% 5 JF
throughput_in_3  = [2.224, 2.243, 2.258, 2.276, 2.291, 2.305];

figure(1);
% Trazar las curvas con diferentes estilos
plot(RecursoEspectral, throughput_in_3, '-rs', 'LineWidth', 2, 'DisplayName', '5 JF');
hold on;
plot(RecursoEspectral, throughput_in_2, '-bs', 'LineWidth', 2, 'DisplayName', '4.5 JF');
plot(RecursoEspectral, throughput_in_1, '-gs', 'LineWidth', 2, 'DisplayName', '4 JF');
hold off;

% Etiquetas
title('Throughput de recepción - 2.5 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Throughput [Gbps]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend('Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([1190 1310]);        % Rango del eje X
%ylim([1.8 2.6]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);

%% Probabilidad de bloqueo

% Probabilidades de bloqueo

% 4 JF
solicitudesBloqueadas_1 = [11.178, 11.066, 10.937, 10.790, 10.630, 10.469];
% 4.5 JF
solicitudesBloqueadas_2 = [10.081, 9.801, 9.485, 9.124, 8.738, 8.212];
% 5 JF
solicitudesBloqueadas_3 = [6.736, 5.169, 3.568, 2.176, 0.747, 0.008];

figure(2);
% Trazar las curvas con diferentes estilos
plot(RecursoEspectral, solicitudesBloqueadas_3, '-rs', 'LineWidth', 2, 'DisplayName', '5 JF');
hold on;
plot(RecursoEspectral, solicitudesBloqueadas_2, '-bs', 'LineWidth', 2, 'DisplayName', '4.5 JF');
plot(RecursoEspectral, solicitudesBloqueadas_1, '-gs', 'LineWidth', 2, 'DisplayName', '4 JF');
hold off;

% Etiquetas
title('Probabilidad de bloqueo - 2.5 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
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
t_delayE2E_C1_1 = [51.923, 51.887, 51.978, 51.899, 51.981, 52.010];
t_delayE2E_C2_1 = [139.470, 134.162, 129.185, 123.555, 118.202, 113.475];
t_delayE2E_C3_1 = [139.855, 134.549, 129.528, 123.922, 118.480, 113.801];
% 4.5 JF
t_delayE2E_C1_2 = [52.348, 52.471, 52.542, 52.420, 52.617, 52.713];
t_delayE2E_C2_2 = [99.636, 94.692, 89.368, 84.816, 80.559, 76.174];
t_delayE2E_C3_2 = [100.098, 95.031, 89.766, 85.226, 80.934, 76.538];
% 5 JF
t_delayE2E_C1_3 = [55.284, 57.527, 56.835, 56.763, 54.609, 49.886];
t_delayE2E_C2_3 = [69.192, 66.526, 62.756, 58.714, 53.211, 46.851];
t_delayE2E_C3_3 = [69.637, 66.980, 63.203, 59.164, 53.702, 47.282];

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
title('Retardos E2E - 2.5 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Retardo [ms]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend({'4 JF - Paquetes clase 1', '4 JF - Paquetes clase 2', '4 JF - Paquetes clase 3', ...
        '4.5 JF - Paquetes clase 1', '4.5 JF - Paquetes clase 2', '4.5 JF - Paquetes clase 3', ...
        '5 JF - Paquetes clase 1', '5 JF - Paquetes clase 2', '5 JF - Paquetes clase 3'}, ...
       'NumColumns', 3, 'Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([0 4]);        % Rango del eje X
ylim([0 185]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);
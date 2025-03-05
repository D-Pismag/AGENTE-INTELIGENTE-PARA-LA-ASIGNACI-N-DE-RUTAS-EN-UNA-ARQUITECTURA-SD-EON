clear; clc; close all;

% ==============================
% ESCENARIO DE RECURSOS LIMITADOS - 2 Gbps
% ==============================

RecursoEspectral = [1200, 1220, 1240, 1260, 1280, 1300]; % Valores de Jumbo Frames considerados

%% Gráfica Throughput

% Throughput

% 3 JF
throughput_in_1  = [1.389, 1.405, 1.422, 1.437, 1.458, 1.479];
% 3.5 JF
throughput_in_2  = [1.563, 1.587, 1.611, 1.634, 1.657, 1.679];
% 4 JF
throughput_in_3  = [1.767, 1.784, 1.797, 1.812, 1.825, 1.837];

figure(1);
% Trazar las curvas con diferentes estilos
plot(RecursoEspectral, throughput_in_3, '-rs', 'LineWidth', 2, 'DisplayName', '4 JF');
hold on;
plot(RecursoEspectral, throughput_in_2, '-bs', 'LineWidth', 2, 'DisplayName', '3.5 JF');
plot(RecursoEspectral, throughput_in_1, '-gs', 'LineWidth', 2, 'DisplayName', '3 JF');
hold off;

% Etiquetas
title('Throughput de recepción - 2 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
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

% 3 JF
solicitudesBloqueadas_1 = [15.327, 14.037, 12.916, 11.645, 11.346, 11.211];
% 3.5 JF
solicitudesBloqueadas_2 = [10.436, 10.225, 10.003, 9.740, 9.464, 9.163];
% 4 JF
solicitudesBloqueadas_3 = [7.269, 6.002, 4.323, 2.964, 1.579, 0.169];

figure(2);
% Trazar las curvas con diferentes estilos
plot(RecursoEspectral, solicitudesBloqueadas_3, '-rs', 'LineWidth', 2, 'DisplayName', '4 JF');
hold on;
plot(RecursoEspectral, solicitudesBloqueadas_2, '-bs', 'LineWidth', 2, 'DisplayName', '3.5 JF');
plot(RecursoEspectral, solicitudesBloqueadas_1, '-gs', 'LineWidth', 2, 'DisplayName', '3 JF');
hold off;

% Etiquetas
title('Probabilidad de bloqueo - 2 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
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
% 3 JF
t_delayE2E_C1_1 = [51.807, 51.758, 51.654, 51.672, 51.632, 51.773];
t_delayE2E_C2_1 = [153.276, 149.975, 146.740, 142.364, 137.266, 132.640];
t_delayE2E_C3_1 = [159.689, 154.244, 149.268, 142.828, 137.558, 132.929];
% 3.5 JF
t_delayE2E_C1_2 = [52.335, 52.276, 52.319, 52.423, 52.548, 52.489];
t_delayE2E_C2_2 = [112.773, 107.365, 102.404, 97.377, 92.506, 87.890];
t_delayE2E_C3_2 = [113.158, 107.610, 102.691, 97.665, 92.838, 88.166];
% 4 JF
t_delayE2E_C1_3 = [53.469, 55.172, 56.485, 56.583, 55.782, 52.760];
t_delayE2E_C2_3 = [71.289, 67.944, 64.496, 60.987, 56.379, 49.970];
t_delayE2E_C3_3 = [71.674, 68.333, 64.892, 61.436, 56.749, 50.337];

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
title('Retardos E2E - 2 Gbps', 'FontSize', 14, 'FontWeight', 'bold');
xlabel('Recurso espectral disponible [\lambda]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Retardo [ms]', 'FontSize', 12, 'FontWeight', 'bold');

% Leyenda
legend({'3 JF - Paquetes clase 1', '3 JF - Paquetes clase 2', '3 JF - Paquetes clase 3', ...
        '3.5 JF - Paquetes clase 1', '3.5 JF - Paquetes clase 2', '3.5 JF - Paquetes clase 3', ...
        '4 JF - Paquetes clase 1', '4 JF - Paquetes clase 2', '4 JF - Paquetes clase 3'}, ...
       'NumColumns', 3, 'Location', 'best', 'FontSize', 10);

% Rejilla en el fondo
grid on;              
grid minor;           % Habilita líneas de cuadrícula menores

% Límites de los ejes
%xlim([0 4]);        % Rango del eje X
ylim([0 185]);    % Rango del eje Y

% Cambiar la fuente y el tamaño en los ejes
set(gca, 'FontName', 'Times New Roman', 'FontSize', 12);
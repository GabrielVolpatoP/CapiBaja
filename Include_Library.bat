@echo off
setlocal

:: Pega o nome do usuário atual
set "usuario=%USERNAME%"

:: Caminho da pasta a ser copiada (substitua com o caminho correto)
set "pasta_origem=E:\Download\CapiBaja-main\libraries"

:: Caminho de destino para onde a pasta será copiada (pasta "Documents\libraries" do usuário)
set "destino=C:\Users\%usuario%\OneDrive\Documentos\Arduino\libraries"

:: Verifica se a pasta de destino existe, e cria se necessário
if not exist "%destino%" (
    mkdir "%destino%"
)

:: Copiando a pasta inteira para o destino (incluindo subpastas e arquivos)
xcopy "%pasta_origem%" "%destino%\" /E /H /I /Y

echo Pasta copiada com sucesso para: %destino%
pause

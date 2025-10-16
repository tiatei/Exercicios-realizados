<!DOCTYPE html>
<html lang="pt pt" > 
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {
      font-family: Helvetica;
      display: inline-block;
      margin: 0px auto;
      text-align: center;
    }
    body {
      background-color: #2196f3; /* azul */
      margin: 0;
      padding: 0;
      /* Removido background-image */
    }
    .sensor-box {
      background: #fff;
      border: 2px solid #e54308;
      border-radius: 8px;
      display: inline-block;
      padding: 20px 40px;
      font-size: 28px;
      margin-top: 40px;
      box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    }
  </style>
</head>
<body>
  <h1>Leituras de Sensor</h1>
  <div class="sensor-box" id="sensorLeitura">
    Leitura do sensor: <span id="valorSensor">---</span>
  </div>
  <script>
    // Exemplo: Atualiza o valor do sensor (substitua pelo valor real via backend ou AJAX)
    document.getElementById('valorSensor').textContent = '123'; // Troque por valor real
  </script>
</body>
</html>
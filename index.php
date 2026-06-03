<?php
include 'db.php';
?>

<!DOCTYPE html>
<html>
<head>
    <title>DHT Monitoring System</title>

    <style>

        body{
            font-family: Arial;
            background:#f2f2f2;
            text-align:center;
        }

        table{
            width:80%;
            margin:auto;
            border-collapse:collapse;
            background:white;
        }

        th,td{
            border:1px solid black;
            padding:10px;
        }

        th{
            background:green;
            color:white;
        }

        h1{
            color:#333;
        }

    </style>

</head>
<body>

<h1>IoT Temperature and Humidity Monitoring</h1>

<table>

<tr>
    <th>ID</th>
    <th>Temperature °C</th>
    <th>Humidity %</th>
    <th>Date Time</th>
</tr>

<?php

$sql = "SELECT * FROM sensor_data ORDER BY id DESC";
$result = $conn->query($sql);

if($result->num_rows > 0){

    while($row = $result->fetch_assoc()){

        echo "<tr>
                <td>".$row['id']."</td>
                <td>".$row['temperature']."</td>
                <td>".$row['humidity']."</td>
                <td>".$row['created_at']."</td>
              </tr>";
    }

}else{

    echo "<tr><td colspan='4'>No Data</td></tr>";
}

$conn->close();

?>

</table>

</body>
</html>
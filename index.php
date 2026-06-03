<?php
include 'db.php';
?>

<!DOCTYPE html>
<html>

<head>

    <title>IoT Ultrasonic Sensor</title>

    <style>

        body{
            font-family: Arial;
            background:#f4f4f4;
            padding:20px;
        }

        table{
            width:100%;
            border-collapse:collapse;
            background:white;
        }

        table, th, td{
            border:1px solid black;
        }

        th, td{
            padding:10px;
            text-align:center;
        }

        th{
            background:#333;
            color:white;
        }

        h2{
            text-align:center;
        }

    </style>

</head>

<body>

<h2>Ultrasonic Sensor Monitoring System</h2>

<table>

<tr>
    <th>ID</th>
    <th>Distance (cm)</th>
    <th>Date & Time</th>
</tr>

<?php

$sql = "SELECT * FROM sensor_data ORDER BY id DESC";

$result = mysqli_query($conn, $sql);

if(mysqli_num_rows($result) > 0){

    while($row = mysqli_fetch_assoc($result)){

        echo "<tr>";

        echo "<td>".$row['id']."</td>";

        echo "<td>".$row['distance']." cm</td>";

        echo "<td>".$row['created_at']."</td>";

        echo "</tr>";

    }

}else{

    echo "<tr><td colspan='3'>No Data Found</td></tr>";

}

?>

</table>

</body>
</html>
<?php

include 'db.php';

if(isset($_GET['temperature']) && isset($_GET['humidity'])) {

    $temperature = $_GET['temperature'];
    $humidity = $_GET['humidity'];

    $sql = "INSERT INTO sensor_data (temperature, humidity)
            VALUES ('$temperature', '$humidity')";

    if ($conn->query($sql) === TRUE) {
        echo "Data inserted successfully";
    } else {
        echo "Error: " . $conn->error;
    }

} else {
    echo "No data received";
}

$conn->close();

?>
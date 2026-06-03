<?php

include 'db.php';

if(isset($_GET['distance'])) {

    $distance = $_GET['distance'];

    $sql = "INSERT INTO sensor_data(distance)
            VALUES('$distance')";

    if(mysqli_query($conn, $sql)) {

        echo "Data inserted successfully";

    } else {

        echo "Error: " . mysqli_error($conn);

    }

} else {

    echo "No data received";

}

?>
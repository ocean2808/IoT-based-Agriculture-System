<?php

include 'db_connect.php';
$conn = OpenCon();

//Creating Array for JSON response
$response = array();

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

// Check if we got the field from the user
if (!empty($_POST['moist']) ) {
 
    $moist = $_POST['moist'];
	$sql = "INSERT INTO moisture(moist) VALUES ('$moist')";
	if ($conn->query($sql) === TRUE) {
        // successfully inserted 
        $response["success"] = 1;
        $response["message"] = "moisture successfully created.";
 
        // Show JSON response
        echo json_encode($response);
    } else {
        // Failed to insert data in database
        $response["success"] = 0;
        $response["message"] = "Something has been wrong";
 
        // Show JSON response
        echo json_encode($response);
    }
} else {
    // If required parameter is missing
    $response["success"] = 0;
    $response["message"] = "Parameter(s) are missing. Please check the request";
 
    // Show JSON response
    echo json_encode($response);
}
?>

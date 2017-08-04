<?php
/**
 * Created by PhpStorm.
 * User: sam
 * Date: 8/4/2017
 * Time: 1:09 PM
 */


$servername = "localhost";
$username = "root";
$password = "";
$database = "sacco";

$action = '';

// Create connection
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}


// function to get all members
$sql = "SELECT *  FROM members";
$members = $conn->query($sql);

// function to get all business ideas
$sql = "SELECT *  FROM ideas";
$ideas = $conn->query($sql);



// function to sub,it user
if (isset($_GET['action'])) {

    switch ($_GET['action']) {
        case 'add_user':
            $full_name = $_POST['fullname'];
            $username = $_POST['username'];
            $password = $_POST['password'];

            echo $full_name . $username . $password;


            $sql = 'INSERT INTO members (fullname, username, password)VALUES ("' . $full_name . '","' . $username . '","' . $password . '")';
            if ($conn->query($sql) === TRUE) {
                echo "New record created successfully";
            } else {
                echo $conn->error;
            }

            break;



        case 'add_business';

        echo $_GET['action'];

            $business = $_POST['business_idea'];
            $business = $_POST['dateOfInvestment'];
            $initial = $_POST['initialInvestment'];

            $sql = 'INSERT INTO ideas (idea, date, initial,status)VALUES ("' .   $business . '","' .   $business . '","' .$initial. '","pending")';
            if ($conn->query($sql) === TRUE) {
                echo "New record created successfully";
            } else {
                echo $conn->error;
            }
            break;
    }

}

?>



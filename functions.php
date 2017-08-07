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
$contributionsFile = "C:/Users/sam/Desktop/contributions.txt";

// Create connection
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}


// function to know the clicked page

if (isset($_GET['page'])) {


    switch ($_GET['page']) {
        // get all member contributions


        case'dashboard':

            /// get members contributions from the text files

            $handle = @fopen($contributionsFile, "r"); //read line one by one
            $values = '';

            while (!feof($handle)) // Loop til end of file.
            {
                $buffer = fgets($handle, 4096); // Read a line.
                list($name, $amount, $date, $receipt) = explode("|", $buffer);//Separate string by the means of |
                $sql = 'INSERT INTO contributions (contributor, Amount,date,receipt_number,status) VALUES ("' . $name . '","' . $amount
                    . '","' . $date . '","' . $receipt . '","pending")';

                $contributions = $conn->query($sql);

            }

            // function to get all members
            $sql = "SELECT *  FROM members";
            $members = $conn->query($sql);
            $totalMembers = mysqli_num_rows($members);
            echo $totalMembers;


            break;


        case 'contributions':
            // function to get all members
            $contributionsSql = "SELECT *  FROM contributions";
            $contributions = $conn->query($contributionsSql);
            break;

        case 'members':
            // function to get all members
            $sql = "SELECT *  FROM members";
            $members = $conn->query($sql);
            break;


        case'investments':

            // function to get all business ideas
            $ideasSql = "SELECT *  FROM ideas";
            $ideas = $conn->query($ideasSql);


            break;

    }
}


// function to submit forms
if (isset($_GET['action'])) {

    switch ($_GET['action']) {

        // function to add a user
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


        // function to add a business idea
        case 'add_business';

            echo $_GET['action'];

            $business = $_POST['business_idea'];
            $business = $_POST['dateOfInvestment'];
            $initial = $_POST['initialInvestment'];

            $sql = 'INSERT INTO ideas (idea, date, initial,status)VALUES ("' . $business . '","' . $business . '","' . $initial . '","pending")';
            if ($conn->query($sql) === TRUE) {
                echo "New record created successfully";
            } else {
                echo $conn->error;
            }
            break;

        case 'accept_contribution':

            $contribution_id = $_GET['id'];
            $contributionSql = "SELECT *  FROM contributions WHERE  ID =  $contribution_id ";
            $result = $conn->query($contributionSql);

            if(mysqli_num_rows( $result)>0){


                $sql="UPDATE contributions SET status = 'confirmed' WHERE ID =  $contribution_id  ";
                if ($conn->query($sql) === TRUE) {
                    echo "record updated";
                } else {
                    echo $conn->error;
                }
            }

            break;

        case 'deny_contribution':

            $contribution_id = $_GET['id'];
            $contributionSql = "SELECT *  FROM contributions WHERE  ID =  $contribution_id ";
            $result = $conn->query($contributionSql);

            if(mysqli_num_rows( $result)>0){


                $sql=" UPDATE contributions SET status = 'denied' WHERE ID =  $contribution_id  ";
                if ($conn->query($sql) === TRUE) {
                    echo "record updated";
                } else {
                    echo $conn->error;
                }
            }

            break;


    }

}


?>



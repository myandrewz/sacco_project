<?php
/**
 * Created by PhpStorm.
 * User: sam
 * Date: 8/4/2017
 * Time: 1:08 PM
 */


require('functions.php')

?>
<!DOCTYPE html>
<html lang="en">

<head>
    <title>mysacco</title>

    <link rel="stylesheet" href="assets/bootstrap/css/bootstrap.min.css">
    <link href="https://fonts.googleapis.com/css?family=Raleway" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css?family=Open+Sans" rel="stylesheet">
    <link rel="stylesheet" href="styles.css">


    <script src="assets/jquery-3.2.1.min.js"></script>
    <script src="assets/bootstrap/js/bootstrap.min.js"></script>
</head>


<body>
<div class="container-fluid">
    <div class="row">
        <div class="col-md-12">
            <div class="row">
                <div class="col-md-2 menu">

                    <ul class="nav nav-sidebar">
                        <li class=" nav-active active">
                            <a href="index.php?page=dashboard"><i class="icon-home"></i><span>Dashboard</span></a>
                        </li>

                        <li class="nav-parent">
                            <a href="index.php?page=members"><i class="icon-bar-chart"></i><span>Members</span></a>

                        </li>

                        <li class="nav-parent">
                            <a href="index.php?page=contributions"><i class="icon-bar-chart"></i><span>Members Contirbutions</span></a>

                        </li>

                        <li class="nav-parent">
                            <a href="index.php?page=loans"><i class="icon-docs"></i><span>Request for Loans </span></a>

                        </li>
                        <li class="nav-parent">
                            <a href="index.php?page=investments"><i
                                        class="icon-drop"></i><span>Investment Details</span></a>

                        </li>
                        <li class="nav-parent">
                            <a href="index.php?page=Reports"><i class="icon-user"></i><span>Reports</span></a>

                        </li>


                    </ul>


                </div>
                <div class="col-md-10 main">
                    <?php


                    switch ($_GET['page']) {

                        case'dashboard' :
                            ?>

                            <div>
                                <h2 style="text-align: center;padding: 40px;font-weight: 500"> MY SACCO ADMIN
                                    PANEL.</h2>

                                <div class="row">
                                    <div class="col-xlg-4 col-lg-4 col-visitors">
                                        <div class="row">
                                            <div class="col-md-12">
                                                <div class="panel these-icons">
                                                    <div class="header-number"><?php echo $totalMembers;?></div>
                                                    <div class="header">Active Members</div>

                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                    <div class="col-xlg-4 col-lg-4 col-visitors">
                                        <div class="row">
                                            <div class="col-md-12">
                                                <div class="panel these-icons">
                                                    <div class="header-number">5,000,000</div>
                                                    <div class="header">Amount loaned out in cash</div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                    <div class="col-xlg-4 col-lg-4 col-visitors">
                                        <div class="row">
                                            <div class="col-md-12">
                                                <div class="panel these-icons">
                                                    <div class="header-number">2,000,000</div>
                                                    <div class="header">Total Conributions</div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <?php

                            break;


                        case'members':
                            ?>
                            <div class="row">
                                <h2 style="text-align: center;padding: 40px;font-weight: 500">MEMBERS</h2>

                                <div class="col-md-6 portlets">
                                    <div class="panel members">
                                        <div class="panel-header">
                                            <h3><i class="fa fa-table"></i> <strong>Members</strong></h3>
                                            <div class="control-btn">
                                                <a href="#" class="panel-reload hidden"><i class="icon-reload"></i></a>
                                                <a class="hidden" id="dropdownMenu1" data-toggle="dropdown">
                                                    <i class="icon-settings"></i>
                                                </a>

                                                <a href="#" class="panel-popout hidden tt" title="Pop Out/In"><i
                                                            class="icons-office-58"></i></a>
                                                <a href="#" class="panel-maximize hidden"><i
                                                            class="icon-size-fullscreen"></i></a>
                                                <a href="#" class="panel-toggle"><i class="fa fa-angle-down"></i></a>
                                                <a href="#" class="panel-close"><i class="icon-trash"></i></a>
                                            </div>
                                        </div>
                                        <div class="panel-content">
                                            <table class="table table-hover">
                                                <thead>
                                                <tr>
                                                    <th>First Name</th>
                                                    <th>Last Name</th>
                                                    <th>Username</th>
                                                </tr>
                                                </thead>
                                                <tbody>
                                                <?php
                                                while ($row = $members->fetch_assoc()) {
                                                    echo "<tr>
                                                        <td>" . $row["fullname"] . "</td>
                                                        <td>" . $row["username"] . " </td>
                                                         <td>" . $row["password"] . "</td>
                                                         </tr>";
                                                }
                                                ?>

                                                </tbody>
                                            </table>
                                        </div>
                                    </div>
                                </div>
                                <div class="col-md-6 portlets">
                                    <div class="panel members">
                                        <div class="panel-header panel-controls">
                                            <h3><i class="fa fa-table"></i> <strong>Add a member</strong> Table</h3>
                                        </div>
                                        <div class="panel-content">
                                            <form method="post" id="add_user" action="functions.php?action=add_user"
                                                  role="form">
                                                <div class="form-group">
                                                    <label class="control-label">Name</label>
                                                    <div class="append-icon">
                                                        <input type="text" name="fullname" class="form-control"
                                                               minlength="3" placeholder="e.g John " required>
                                                    </div>
                                                </div>
                                                <div class="form-group">
                                                    <label class="control-label">Username</label>
                                                    <div class="append-icon">
                                                        <input type="text" name="username" class="form-control"
                                                               minlength="3" placeholder="UserName" required>
                                                        <i class="icon-user"></i>
                                                    </div>
                                                </div>
                                                <div class="form-group">
                                                    <label class="control-label">Password</label>
                                                    <div class="append-icon">
                                                        <input type="password" name="password" class="form-control"
                                                               minlength="3" placeholder="password" required>
                                                        <i class="icon-user"></i>
                                                    </div>
                                                </div>
                                                <button type="submit" class="btn btn-embossed btn-primary">SAVE</button>

                                                <br>
                                                <div class="loader"></div>

                                                <br><br>

                                                <div class="alert alert-success alert-dismissable">

                                                    <button type="button" class="close" data-dismiss="alert"
                                                            aria-hidden="true">
                                                        ×
                                                    </button>
                                                    Member added.
                                                </div>


                                            </form>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <?php
                            break;

                        case 'contributions':
                            ?>
                            <div class="row">
                                <h2 style="text-align: center;padding: 40px;font-weight: 500">MEMBER CONTRIBUTIONS</h2>

                                <div class="col-md-12 portlets">
                                    <div class="panel  members">
                                        <div class="panel-header">
                                            <h3><i class="fa fa-table"></i> <strong>CONTRIBUTIONS</strong> TABLE
                                            </h3>
                                            <div class="control-btn">
                                                <a href="#" class="panel-reload hidden"><i class="icon-reload"></i></a>
                                                <a class="hidden" id="dropdownMenu1" data-toggle="dropdown">
                                                    <i class="icon-settings"></i>
                                                </a>

                                                <a href="#" class="panel-popout hidden tt" title="Pop Out/In"><i
                                                            class="icons-office-58"></i></a>
                                                <a href="#" class="panel-maximize hidden"><i
                                                            class="icon-size-fullscreen"></i></a>
                                                <a href="#" class="panel-toggle"><i class="fa fa-angle-down"></i></a>
                                                <a href="#" class="panel-close"><i class="icon-trash"></i></a>
                                            </div>
                                        </div>
                                        <div class="panel-content">
                                            <table class="table table-hover">
                                                <thead>
                                                <tr>
                                                    <th>Member</th>
                                                    <th>Contribution</th>
                                                    <th>status</th>
                                                    <th>Action</th>
                                                </tr>
                                                </thead>
                                                <tbody>
                                                <?php
                                                while ($row = $contributions->fetch_assoc()) {
                                                    echo "<tr>
                                                        <td>" . $row["contributor"] . "</td>
                                                        <td>" . $row["Amount"] . " </td>
                                                         <td>" . $row["status"] . "</td>"
                                                         ?>
                                                          <td><?php if($row["status"] =='pending'){?><a href="functions.php?action=accept_contribution&id=<?php  echo $row["ID"] ?>">accept</a>&nbsp;| &nbsp;
                                                              <a href=functions.php?action=deny_contribution&id=<?php  echo $row["ID"] ?>>deny</a><?php } ?></td>
                                                         </tr>
                                                    <?php ;
                                                }
                                                ?>
                                                </tbody>
                                            </table>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <?php
                            break;

                        case 'loans':
                            ?>
                            <div class="row">
                                <h2 style="text-align: center;padding: 40px;font-weight: 500">REQUEST FOR LOANS</h2>

                                <div class="col-md-12 portlets">
                                    <div class="panel  members">
                                        <div class="panel-header">
                                            <h3><i class="fa fa-table"></i> <strong>REQUEST FOR LOANS</strong> TABLE
                                            </h3>
                                            <div class="control-btn">
                                                <a href="#" class="panel-reload hidden"><i class="icon-reload"></i></a>
                                                <a class="hidden" id="dropdownMenu1" data-toggle="dropdown">
                                                    <i class="icon-settings"></i>
                                                </a>

                                                <a href="#" class="panel-popout hidden tt" title="Pop Out/In"><i
                                                            class="icons-office-58"></i></a>
                                                <a href="#" class="panel-maximize hidden"><i
                                                            class="icon-size-fullscreen"></i></a>
                                                <a href="#" class="panel-toggle"><i class="fa fa-angle-down"></i></a>
                                                <a href="#" class="panel-close"><i class="icon-trash"></i></a>
                                            </div>
                                        </div>
                                        <div class="panel-content">
                                            <table class="table table-hover">
                                                <thead>
                                                <tr>
                                                    <th>#</th>
                                                    <th>First Name</th>
                                                    <th>Last Name</th>
                                                    <th>status</th>
                                                    <th>Amount</th>
                                                    <th>Action</th>
                                                </tr>
                                                </thead>
                                                <tbody>
                                                <tr>
                                                    <td>1</td>
                                                    <td>Mark</td>
                                                    <td>Otto</td>
                                                    <td>Pending</td>
                                                    <td>2,000,000</td>
                                                    <td><a href="">accept</a>&nbsp;| &nbsp;<a href="">deny</a></td>
                                                </tr>
                                                <tr>
                                                    <td>2</td>
                                                    <td>Jacob</td>
                                                    <td>Thornton</td>
                                                    <td>Pending</td>
                                                    <td>4,000,000</td>
                                                    <td><a href="">accept</a>&nbsp;| &nbsp;<a href="">deny</a></td>
                                                </tr>
                                                <tr>
                                                    <td>3</td>
                                                    <td>Larry</td>
                                                    <td>Kings</td>
                                                    <td>Pending</td>
                                                    <td>1,000,000</td>
                                                    <td><a href="">accept</a>&nbsp;| &nbsp;<a href="">deny</a></td>
                                                </tr>
                                                <tr>
                                                    <td>4</td>
                                                    <td>Steve</td>
                                                    <td>Urkel</td>
                                                    <td>Success</td>
                                                    <td>300,000</td>
                                                    <td><a href="">accept</a>&nbsp;| &nbsp;<a href="">deny</a></td>
                                                </tr>
                                                </tbody>
                                            </table>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <?php
                            break;

                        case 'investments':
                            ?>
                            <div class="row">
                                <h2 style="text-align: center;padding: 40px;font-weight: 500">INVESTMENTS DETAILS</h2>

                                <div class="col-md-12 portlets">
                                    <div class="panel members">
                                        <div class="panel-header">
                                            <h3><strong>ADD INVESTMENTS DETAILS</strong></h3>
                                            <div class="control-btn">
                                                <a href="#" class="panel-reload hidden"><i class="icon-reload"></i></a>
                                                <a class="hidden" id="dropdownMenu1" data-toggle="dropdown">
                                                    <i class="icon-settings"></i>
                                                </a>

                                                <a href="#" class="panel-popout hidden tt" title="Pop Out/In"><i
                                                            class="icons-office-58"></i></a>
                                                <a href="#" class="panel-maximize hidden"><i
                                                            class="icon-size-fullscreen"></i></a>
                                                <a href="#" class="panel-toggle"><i class="fa fa-angle-down"></i></a>
                                                <a href="#" class="panel-close"><i class="icon-trash"></i></a>
                                            </div>
                                        </div>
                                        <div class="panel-content">
                                            <form role="form" class="form-validation" method="post" id="add_business">
                                                <div class="row">
                                                    <div class="col-sm-6">
                                                        <div class="form-group">
                                                            <label class="control-label">Business Idea</label>
                                                            <div class="append-icon">
                                                                <textarea name="business_idea" class="form-control"
                                                                          id="" cols="20" rows="5"></textarea>

                                                            </div>
                                                        </div>
                                                    </div>
                                                    <div class="col-sm-6">
                                                        <div class="form-group">
                                                            <label class="control-label">Date of Investment</label>
                                                            <div class="append-icon">
                                                                <input type="date" name="dateOfInvestment"
                                                                       class="form-control"
                                                                       minlength="4"
                                                                       placeholder="Minimum 4 characters..." required>

                                                            </div>
                                                        </div>
                                                    </div>
                                                </div>
                                                <div class="row">
                                                    <div class="col-sm-6">
                                                        <div class="form-group">
                                                            <label class="control-label">Initial investment
                                                                Price</label>
                                                            <div class="append-icon">
                                                                <input type="number" name="initialInvestment"
                                                                       class="form-control"
                                                                       placeholder="price " required>

                                                            </div>
                                                        </div>
                                                    </div>
                                                    <div class="col-sm-6">
                                                        <div class="form-group">
                                                            <label class="control-label">Profits percentage</label>
                                                            <div class="append-icon">
                                                                <input type="number" name="mobile" class="form-control"
                                                                       placeholder="Profits percentage">

                                                            </div>
                                                        </div>
                                                    </div>
                                                </div>

                                                <div class="text-center  m-t-20">
                                                    <button type="submit" class="btn btn-embossed btn-primary">SAVE
                                                    </button>

                                                </div>
                                                <div class="loader"></div>

                                                <br><br>

                                                <div class="alert alert-success alert-dismissable">

                                                    <button type="button" class="close" data-dismiss="alert"
                                                            aria-hidden="true">
                                                        ×
                                                    </button>
                                                    Business idea added.
                                                </div>


                                            </form>
                                        </div>
                                    </div>
                                </div>


                                <div class="col-md-12 portlets">
                                    <div class="panel  members">
                                        <div class="panel-header">
                                            <h3><i class="fa fa-table"></i> <strong>BUSINESS IDEAS</strong> TABLE
                                            </h3>
                                            <div class="control-btn">
                                                <a href="#" class="panel-reload hidden"><i class="icon-reload"></i></a>
                                                <a class="hidden" id="dropdownMenu1" data-toggle="dropdown">
                                                    <i class="icon-settings"></i>
                                                </a>

                                                <a href="#" class="panel-popout hidden tt" title="Pop Out/In"><i
                                                            class="icons-office-58"></i></a>
                                                <a href="#" class="panel-maximize hidden"><i
                                                            class="icon-size-fullscreen"></i></a>
                                                <a href="#" class="panel-toggle"><i class="fa fa-angle-down"></i></a>
                                                <a href="#" class="panel-close"><i class="icon-trash"></i></a>
                                            </div>
                                        </div>
                                        <div class="panel-content">
                                            <table class="table table-hover">
                                                <thead>
                                                <tr>
                                                    <th>Idea</th>
                                                    <th>Date of investment</th>
                                                    <th>Amount</th>
                                                    <th>status</th>
                                                    <th>Action</th>
                                                </tr>
                                                </thead>
                                                <tbody>
                                                <?php
                                                while ($row = $ideas->fetch_assoc()) {
                                                    echo "<tr>
                                                        <td>" . $row["idea"] . "</td>
                                                        <td>" . $row["date"] . " </td>
                                                         <td>" . $row["initial"] . "</td>
                                                          <td>" . $row["status"] . "</td>
                                                         <td><a href=\"\">accept</a>&nbsp;| &nbsp;<a href=\"\">deny</a></td>
                                                         </tr>";
                                                }
                                                ?>


                                                </tbody>
                                            </table>
                                        </div>
                                    </div>
                                </div>
                            </div>

                            <br><br><br>
                            <?php

                            break;

                        case 'Reports':
                            ?>

                            <div class="row" style="margin-top: 30px">
                                <div class="col-md-12">
                                    <h2 style="text-align: center;padding: 40px;font-weight: 500">REPORTS</h2>
                                    <div class="col-xlg-4 col-financial-stocks">
                                        <div class="panel members">
                                            <div class="panel-header panel-controls">
                                                <h3><i class="icon-graph"></i> <strong>BENEFITS PER USER OVER
                                                        TIME</strong></h3>
                                            </div>
                                            <div class="panel-content widget-full widget-stock stock1">
                                                <div class="tabs tabs-linetriangle">
                                                    <ul class="nav nav-tabs nav-4" role="tablist">
                                                        <li class="nav-item lines-3" role="tab" data-toggle="tab">
                                                            <a href="#microsoft-tab" id="microsoft" data-toggle="tab">
                                                                <span class="title">Samuel</span>
                                                                <span class="c-green">+6.214%</span>
                                                            </a>
                                                        </li>
                                                        <li class="nav-item active lines-3" role="tab"
                                                            data-toggle="tab">
                                                            <a href="#sony-tab" id="sony" data-toggle="tab">
                                                                <span class="title">Daniel</span>
                                                                <span class="c-green">-8.425%</span>
                                                            </a>
                                                        </li>
                                                        <li class="nav-item lines-3" role="tab" data-toggle="tab">
                                                            <a href="#samsung-tab" id="samsung" data-toggle="tab">
                                                                <span class="title">Aaron</span>
                                                                <span class="c-green">+2.035%</span>
                                                            </a>
                                                        </li>
                                                        <li class="nav-item lines-3" role="tab" data-toggle="tab">
                                                            <a href="#apple-tab" id="apple" data-toggle="tab">
                                                                <span class="title">Emmanuel</span>
                                                                <span class="c-green">+1.245%</span>
                                                            </a>
                                                        </li>
                                                    </ul>
                                                    <div class="tab-content">
                                                        <div role="tabpanel" class="tab-pane" id="microsoft-tab">
                                                            <div id="stock-microsoft"></div>
                                                        </div>
                                                        <div role="tabpanel" class="tab-pane active" id="sony-tab">
                                                            <div id="stock-sony"></div>
                                                        </div>
                                                        <div role="tabpanel" class="tab-pane" id="samsung-tab">
                                                            <div id="stock-samsung"></div>
                                                        </div>
                                                        <div role="tabpanel" class="tab-pane" id="apple-tab">
                                                            <div id="stock-apple"></div>
                                                        </div>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <?php
                            break;

                    }
                    ?>


                </div>
            </div>
        </div>
    </div>


    <footer class="footer">Copyright @2017</footer>
</div>

<script>
    $(function () {

        $('#add_user').on('submit', function (e) {

            e.preventDefault();
            $('.loader').css('display', 'block');
            $.ajax({
                type: 'post',
                url: 'functions.php?action=add_user',
                data: $('#add_user').serialize(),
                success: function (response) {
                    $('.loader').css('display', 'none');
                    $('.alert').css('display', 'block');
                    $('#add_user').reset();
                    console.log(response)
                }
            });

        });

        $('#add_business').on('submit', function (e) {

            e.preventDefault();
            $('.loader').css('display', 'block');
            $.ajax({
                type: 'post',
                url: 'functions.php?action=add_business',
                data: $('#add_business').serialize(),
                success: function (response) {
                    $('.loader').css('display', 'none');
                    $('.alert').css('display', 'block');
                    $('#add_business').reset();
                    console.log(response)
                }
            });

        });

    });
</script>
</body>
</html>



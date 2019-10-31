<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Invoice</title>
    <style>
        table#cart, tr#cart, td#cart {
            border: solid 1px black;
            border-collapse: collapse;
            padding: 5px 5px 5px 5px;
        }
    </style>
</head>
<body>
    <center>
        <h1><a href="../index.html"><b>Taylor's Website</b></a></h1> <br />
        <table style="border-spacing: 100px 0">
            <tr>
                <td><a href="../lab1/index.html">lab1</a></td>
                <td><a href="../lab2/index.html">lab2</a></td>
                <td><a href="../lab3/index.html">lab3</a></td>
                <td><a href="../lab4/index.html">lab4</a></td>
                <td><a href="../lab5/index.html">lab5</a></td>
                <td><a href="../lab6/index.html">lab6</a></td>
                <td><a href="../lab7/index.html">lab7</a></td>
                <td><a href="../lab8/index.html">lab8</a></td>
            </tr>
        </table>
        <hr />
    </center>
    <h1>CSCI Store Invoice</h1>
    <?php
        $techArray = array("Desktop", "Laptop", "Drive", "RAM");
        $checkArray = $_POST['electronics'];
        if(empty($checkArray)) {
            echo "Cart is empty.";
        }
        else {
            $total = 0;
            echo "  <table id='cart'>
                        <tr id='cart'>
                            <td id='cart'>Item</td>
                            <td id='cart'>Price</td>
                        </tr>";
            for($i = 0; $i < sizeof($_POST['electronics']); $i++) {            
                if($checkArray[$i].checked) {
                    if($checkArray[$i] == "Desktop") {
                        $price = 1234;
                    }
                    else if($checkArray[$i] == "Laptop") {
                        $price = 2345;
                    }
                    else if($checkArray[$i] == "10TB Disk Drive") {
                        $price = 246;
                    }
                    else if($checkArray[$i] == "8GB RAM") {
                        $price = 79;
                    }
                    $total += $price;
                    echo "  <tr id='cart'>
                                <td id='cart'>$checkArray[$i]</td>
                                <td id='cart'>$$price</td>
                            </tr>";
                }   
            }
            echo "<tr id='cart'><td id='cart' style='border: none'>Total: $$total</td><td style='border: none'></td></tr></table>";
        }
    ?>
    <div style="padding-top: 20px;">
        <a href="store.html">Back to store</a>
    </div>
</body>
</html>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Receipt</title>
</head>
<body>
    <?php
        $user = $_POST['user'];
        $pass = $_POST['pass'];
        $shipping = $_POST['shipping'];
        $payment = $_POST['payment'];
        $parts = $_POST['part'];
        $partStr = '';
        $total = 0;

        if($pass != "hellothere7") {
            echo "Password incorrect!";
            echo "<br /><a href='problem3.html'>Return to Store</a>";
        }
        else {
            echo "Username: " . "$user" . "<br />";
            echo "Shipping Method: " . "$shipping" . "<br />";
            echo "Payment Type and Shipping Cost: " . "$payment" . ", $";

            if($shipping == 'USPS') {
                $total += 5;
            }
            if($shipping == 'Fedex') {
                $total += 15;
            }
            if($shipping == 'UPS') {
                $total += 10;
            }
            
            echo "$total" . "<br />";
            echo "Part(s) Purchased: ";

            for($i = 0; $i < sizeof($_POST['part']); $i++) {            
                if($parts[$i].checked) {
                    if($parts[$i] == 'CPU') {
                        $price = 300;
                    }
                    else if($parts[$i] == 'Hard Drive') {
                        $price = 100;
                    }
                    else if($parts[$i] == 'Monitor') {
                        $price = 200;
                    }
                    $total += $price;
                    echo "$parts[$i]" . ", ";
                }
            }
            echo "<br />Total: $" . "$total" . "<br />";
            echo "<a href='problem3.html'>Return to Store</a";
        }
        
    ?>
</body>
</html>
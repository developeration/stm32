$Port=9000
$server = "win-agent"
$database = "STM32DB"




$endpoint = New-Object System.Net.IPEndPoint([System.Net.IPAddress]::any,$Port)
$udpclient = New-Object System.Net.Sockets.UDPClient($Port) 

while($true){
    $receivemessage = $udpclient.Receive([System.Management.Automation.PSReference]$EndPoint)
    $reqstr =  [System.Text.Encoding]::ASCII.GetString($receivemessage)
    Get-Date
    Write-Host $reqstr

$sql = @"
DECLARE @content nvarchar(500) = '$reqstr'

INSERT INTO [dbo].[GPSLog]  ([content])  VALUES (@content)
"@

    $SqlConnection = New-Object System.Data.SqlClient.SqlConnection
    $SqlConnection.ConnectionString = "Server=$server;Database=$database;Integrated Security=SSPI;"
    $SqlCmd = New-Object System.Data.SqlClient.SqlCommand
    $SqlCmd.CommandText = $sql
    $SqlCmd.Connection = $SqlConnection
    $SqlConnection.open()
    $x=$SqlCmd.ExecuteNonQuery()
    $SqlConnection.Close()




    try{
        if($reqstr.IndexOf("CIPGSMLOC:") -gt 0 ){
            $datasplit = $reqstr.Substring(11,$reqstr.Length-11).Split(",")
            if($datasplit.Length -eq 5){
                $latitude = $datasplit[1]
                $longitude = $datasplit[2]
       
$sql = @"
DECLARE @latitude nvarchar(50) = '$latitude'
DECLARE @longitude nvarchar(50) = '$longitude'


INSERT INTO [dbo].[GPSRecord]
([latitude],[longitude],[recordtype])
VALUES
( @latitude,@longitude ,2)
"@

                #$SqlConnection = New-Object System.Data.SqlClient.SqlConnection
                #$SqlConnection.ConnectionString = "Server=$server;Database=$database;Integrated Security=SSPI;"
                $SqlCmd = New-Object System.Data.SqlClient.SqlCommand
                $SqlCmd.CommandText = $sql
                $SqlCmd.Connection = $SqlConnection
                $SqlConnection.open()
                $x=$SqlCmd.ExecuteNonQuery()
                $SqlConnection.Close()
            }
        }
    }catch
    {
        Write-Host $_
    }
    Write-Host "Recorded ~"
}


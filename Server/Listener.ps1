$Port=9000
$server = "win-agent"
$database = "STM32DB"


$endpoint = new-object System.Net.IPEndPoint ([ipaddress]::any,$Port)
$listener = new-object System.Net.Sockets.TcpListener $endpoint 
$listener.start()



while($true){
    $data = $listener.AcceptTcpClient()
    $stream = $data.GetStream() 
    $reqstr = ""
    Get-Date
    try{
        $bytes = New-Object System.Byte[] 1024
        while (($i = $stream.Read($bytes,0,$bytes.Length)) -ne 0){
            $EncodedText = New-Object System.Text.ASCIIEncoding
            $reqstr = $EncodedText.GetString($bytes,0, $i)
            Write-Host $reqstr 
            }
        }
    finally{
        $stream.close()
        }

    try{
    #$data = "+CIPGSMLOC: 0,40.033862,116.263082,2000/01/01,04:53:41"
        if($reqstr.IndexOf("CIPGSMLOC:") -gt 0 ){
            $datasplit = $reqstr.Substring(11,$reqstr.Length-11).Split(",")
            if($datasplit.Length -eq 5){
                $latitude = $datasplit[1]
                $longitude = $datasplit[2]

                Write-Host $latitude "~" $longitude
       
$sql = @"
DECLARE @latitude nvarchar(50) = '$latitude'
DECLARE @longitude nvarchar(50) = '$longitude'


INSERT INTO [dbo].[GPSRecord]
([latitude]
,[longitude])
VALUES
( @latitude,@longitude )
"@

                $SqlConnection = New-Object System.Data.SqlClient.SqlConnection
                $SqlConnection.ConnectionString = "Server=$server;Database=$database;Integrated Security=SSPI;"
                $SqlCmd = New-Object System.Data.SqlClient.SqlCommand
                $SqlCmd.CommandText = $sql
                $SqlCmd.Connection = $SqlConnection
                $SqlConnection.open()
                $SqlCmd.ExecuteNonQuery()
                $SqlConnection.Close()
            }
        }
    }catch
    {
        Write-Host $_
    }
}
$listener.stop()

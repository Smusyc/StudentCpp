<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="WebApplication2Practice.Отчёты_по_данным" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            Введите адрес логов сервера :&nbsp;
            <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
&nbsp;
            <asp:Button ID="Analizer" runat="server" Text="Анализ" OnClick="Analizer_Click" />
            <br />
            <br />
            Примечания:
            <br />
            1)Вводить категорию товаров и период, как они записываются в логах;<br />
            2)Запись XX означает, что определить страну пользователя по IP - невозможно<br />
            3)Время ведётся относително записей в логах сервера</div>
        <p>
            <meta charset="utf-8" />
            1.Отчёт: <b id="docs-internal-guid-605a7663-7fff-12d4-bc1c-95c023225016" style="font-weight:normal;"><span style="font-size:12pt;font-family:Roboto,sans-serif;color:#000000;background-color:transparent;font-weight:400;font-style:normal;font-variant:normal;text-decoration:none;vertical-align:baseline;white-space:pre;white-space:pre-wrap;">Сколько брошенных (не оплаченных) корзин имеется за определенный период?</span></b></p>
        <p>
            Введите период: до
            <asp:TextBox ID="TextBox3" runat="server"></asp:TextBox>
&nbsp;</p>
        <p>
            <meta charset="utf-8" />
            <b id="docs-internal-guid-86c7b127-7fff-0fcc-168d-c2d63b9bcf87" style="font-weight:normal;"><span style="font-size:12pt;font-family:Roboto,sans-serif;color:#000000;background-color:transparent;font-weight:400;font-style:normal;font-variant:normal;text-decoration:none;vertical-align:baseline;white-space:pre;white-space:pre-wrap;">2.Отчёт: Посетители из каких стран совершают больше всего действий на сайте?</span></b></p>
        <p>
            <meta charset="utf-8" />
            3<b id="docs-internal-guid-602b591a-7fff-4213-f5f6-386d2172342f" style="font-weight:normal;"><span style="font-size:12pt;font-family:Roboto,sans-serif;color:#000000;background-color:transparent;font-weight:400;font-style:normal;font-variant:normal;text-decoration:none;vertical-align:baseline;white-space:pre;white-space:pre-wrap;"><b id="docs-internal-guid-86c7b127-7fff-0fcc-168d-c2d63b9bcf88" style="font-weight:normal;">.Отчёт: </b>В какое время суток чаще всего просматривают определенную
            <meta charset="utf-8" />
            <b id="docs-internal-guid-088d17b0-7fff-5ef3-0d48-4da8e3b743e0" style="font-weight:normal;">категорию товаров?</b></span></b></p>
        <p>
            Введите категорию товара:&nbsp;
            <asp:TextBox ID="TextBox4" runat="server"></asp:TextBox>
        </p>
        <p>
            <meta charset="utf-8" />
            <b id="docs-internal-guid-7ce05eee-7fff-ed19-5923-53a4f93f822e" style="font-weight:normal;"><span style="font-size:12pt;font-family:Roboto,sans-serif;color:#000000;background-color:transparent;font-weight:400;font-style:normal;font-variant:normal;text-decoration:none;vertical-align:baseline;white-space:pre;white-space:pre-wrap;">4. <b id="docs-internal-guid-602b591a-7fff-4213-f5f6-386d2172342f0" style="font-weight: normal;"><span style="font-size: 12pt; font-family: Roboto,sans-serif; color: #000000; background-color: transparent; font-weight: 400; font-style: normal; font-variant: normal; text-decoration: none; vertical-align: baseline; white-space: pre; white-space: pre-wrap;"><b id="docs-internal-guid-86c7b127-7fff-0fcc-168d-c2d63b9bcf89" style="font-weight: normal;">Отчёт: </b></span></b>Какая нагрузка (число запросов) на сайт за астрономический час?</span></b></p>
        <p>
            <asp:Label ID="Report" runat="server" Text="Отчёт:" Font-Overline="False" Height="105px" Width="1004px"></asp:Label>
        </p>
    </form>
 </body>
</html>

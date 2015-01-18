<!DOCTYPE HTML>
<html lang="en" encoding="utf-8">
  <head>
    <title>(##total_todos##) Todo listing of ##dbg_address##</title>
    <link type="text/css" href="/default/resources/style.css" rel="stylesheet">
    <script type="text/javascript" src="/default/resources/alert.js"></script>
  </head>
  <body>
    <h1 class="header">Welcome to ##dbg_address##</h1>
    <div id="container">

      <h3>Some debug information</h3>
      <table class="dump">
        <tr>
          <th>Key</th>
          <th>Value</th>
        </tr>
        <tr>
          <td class="key"><code>Servlet's address</code></td>
          <td class="value"><code>##dbg_address##</code></td>
        </tr>

        <tr>
          <td class="key"><code>Servlets's db_file</code></td>
          <td class="value"><code>##dbg_db_file##</code></td>
        </tr>

        <tr>
          <td class="key"><code>Servlets's resources</code></td>
          <td class="value"><code>##dbg_resources##</code></td>
        </tr>

        <tr>
          <td class="key"><code>Servlets's templates</code></td>
          <td class="value"><code>##dbg_templates##</code></td>
        </tr>

        <tr>
          <td class="key"><code>javascript test</code></td>
          <td class="value"> <code><a href="javascript:show_alert()">Test Javascript</a></code></td>
        </tr>
      </table>

      <h3>You have ##total_todos## element(s) in the list</h3>
      <table class="todos">
        <tr><th>Index</th><th>Title</th><th>Body</th><th>Priority</th></tr>

        <!-- #BEGINTABLE todo -->
        <tr>
          <td class="index">##todo_index##</td>
          <td class="title">##todo_title##</td>
          <td class="body">##todo_body##</td>
          <td class="priority">##todo_priority##</td>
        </tr>
        <!-- #ENDTABLE todo -->
      </table>
    </div>
  </body>
</html>

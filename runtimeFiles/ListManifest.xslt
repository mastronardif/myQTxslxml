<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="yes"/>
<!--last Modified ______ 11:12AM
Purpose:  Used to create ____ for report ___,
-->

<xsl:template match="/">
<html>
    

 	<table>	 
	<tr>
<th>name</th>
  <th>path</th>
  </tr>
            <xsl:for-each select="RCC/file">
        <!--select="//TITLE">-->		
		<tr>
			<td>
			<span> <xsl:value-of select="@n" /> </span>
			</td>
                        <td>
                        <span> <xsl:value-of select="@p" /> </span>
                        </td>
		</tr>		
    </xsl:for-each>
    <tr>
    <td>
    count
    </td>
    <td>
    <xsl:value-of select="count(RCC/file)"/>
    </td>
    </tr>
	
	</table>
</html>

 </xsl:template>
 

</xsl:stylesheet>

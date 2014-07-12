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
<th>S</th>
  <th>d</th> 
  <th>t</th>
  <th>q's</th>
  <th>s's</th>
  </tr>
	    <xsl:for-each select="ROOT/C/SN">
        <!--select="//TITLE">-->
		
		<tr>
			<td>
			<span> <xsl:value-of select="@n" /> </span>
			</td>
			<td>
			<xsl:value-of select="@d" />
			</td>
			<td>
			<xsl:value-of select="@t" />
			</td>
			<td>
			<xsl:value-of select="count(QUESTIONS/q)"/>
			</td>
			<td>
			<xsl:value-of select="count(S)"/>
			</td>
		</tr>
		
    </xsl:for-each>
	
	</table>
</html>

 </xsl:template>
 

</xsl:stylesheet>

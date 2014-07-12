<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="yes"/>
<!--last Modified ______ 11:12AM
Purpose:  Used to create ____ for report ___,
-->

<xsl:template match="/">
<html>
    

        <table border="1">
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

<xsl:for-each select="./QUESTIONS/q">

<xsl:choose>
  <xsl:when test="@id ='q2' ">
<xsl:if test="@id ='q2' ">

<br/><xsl:value-of select="@possiblePoints" /> =>


<xsl:call-template name="replace-string">
                        <xsl:with-param name="text"   select="@possiblePoints" />
                        <xsl:with-param name="replace"  select='"1.00"'/>
                        <xsl:with-param name="with"   select='"3.21"'/>
</xsl:call-template>
</xsl:if>
</xsl:when>
<xsl:otherwise>
<br/><xsl:value-of select="@possiblePoints" />
</xsl:otherwise>
</xsl:choose>

</xsl:for-each>

			</td>
			<td>
			<xsl:value-of select="count(S)"/>
<xsl:for-each select="./S">
<br/><xsl:value-of select="@StudentId" />

</xsl:for-each>
			</td>
		</tr>
		
    </xsl:for-each>
	
	</table>
</html>

 </xsl:template>

  <xsl:template name="replace-string">
    <xsl:param name="text"/>
    <xsl:param name="replace"/>
    <xsl:param name="with"/>
    <xsl:choose>
      <xsl:when test="contains($text,$replace)">
        <xsl:value-of select="substring-before($text,$replace)"/>
        <xsl:value-of select="$with"/>
        <xsl:call-template name="replace-string">
          <xsl:with-param name="text"
select="substring-after($text,$replace)"/>
          <xsl:with-param name="replace" select="$replace"/>
          <xsl:with-param name="with" select="$with"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$text"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>


 

</xsl:stylesheet>

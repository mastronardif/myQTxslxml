<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:import href="Identity.xsl"/>
<xsl:template match="/">
<!-- q(/ssn/p[@idx='2']/@anspt)=(<xsl:value-of select="/ssn/p[@idx='2']/@anspt"/>) -->


<!--
<xsl:variable name="myVarA" select="/ROOT/C/SN/QUESTIONS/q[@id='q2']/@AveragePercent"/>
<xsl:value-of select="$myVarA"/>
-->
q(@AveragePercent)=(<xsl:value-of select="/ROOT/C/SN[@n='Session 4']/QUESTIONS/q[@id='q2']/@AveragePercent"/>)

what do you want
numboer of poles(p)
<xsl:value-of select="count(/ssn/p)" />

<!--
 -->

<xsl:copy-of select="ssn/p"/>
<xsl:for-each select="ssn/p/v[1]">
<xsl:copy-of select="expression"/>
<li><xsl:value-of select="." /></li>
<xsl:value-of select="@id"/>
,
<xsl:value-of select="local-name()" />
<xsl:value-of select="text()" />
 </xsl:for-each>


sss
<xsl:copy-of select="/ssn/p[@idx='27']"/>


q(@AveragePercent)=(<xsl:value-of select="/ssn/p/SN[@n='Session 4']/QUESTIONS/q/*"/>)

</xsl:template>

<xsl:template match="/sss">
    <h2><xsl:value-of select="text()" /></h2>

<xsl:value-of select="/ssn/p[@idx='27']/@*" />
</xsl:template>

  <xsl:template match="/ssn/p[@idx='27']">
  zz
     <!-- This will construct a "date" attribute having value of its content -->
     <xsl:attribute name="n">
       <!-- Change what's in here to construct the "new" date format -->
       <xsl:value-of select="concat('newcsnQqn-',.)"/>
     </xsl:attribute>
  </xsl:template>


</xsl:stylesheet>

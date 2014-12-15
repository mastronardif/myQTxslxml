<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="node()|@*">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>
<!-- -->

<xsl:template match="/ssn">
  <xsl:call-template name="MarkQuestion"/>
</xsl:template>


<xsl:template name="MarkQuestion">

	<xsl:variable name="thePs">
	<xsl:for-each select="./p">
	<xsl:copy-of select="." />
	</xsl:for-each>
	</xsl:variable>

	<!-- <xsl:copy-of select="$thePs" /> -->
	<xsl:variable name="thePs22">
	<xsl:call-template name="makeRespLs">
        <xsl:with-param name="pVotes" select="$thePs"/>
    </xsl:call-template>
    </xsl:variable>

the Head
<xsl:variable name="theSSN">
	<xsl:call-template name="makeSSN">
        <xsl:with-param name="head" select="/ssn/@*"/>
    </xsl:call-template>
    </xsl:variable>
    <xsl:copy-of select="$theSSN" />

    <xsl:copy-of select="$thePs22" />

</xsl:template>

<xsl:template name="makeSSN">
        <xsl:param name="head"/>
        <HEAD>
        <xsl:copy-of select="$head" />
    </HEAD>
 </xsl:template>       

<xsl:template name="makeRespLs">
        <xsl:param name="pVotes"/>
        <xsl:copy-of select="$pVotes" />
 </xsl:template>       
</xsl:stylesheet>
<!-- 
	<xsl:copy-of select="." />
<xsl:value-of select="." />

	-->
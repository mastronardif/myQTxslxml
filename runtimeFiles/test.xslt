<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="node()|@*">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>
<!-- -->

<xsl:variable name="xxx">d</xsl:variable>
<xsl:variable name="numofResps"><xsl:value-of select="count(ssn/p[@isDel='N'])"/></xsl:variable>
<xsl:variable name="MinPart_S"><xsl:value-of select="ssn/@MinPart_S"/></xsl:variable>

<xsl:variable name="_minrep">
<xsl:call-template name="Calc_minrep">
        <xsl:with-param name="myNode" select="makeRespLs00"/>
        
    </xsl:call-template>
</xsl:variable>

	<xsl:template match="ssn/@minrep">
  <xsl:attribute name="minrep"><xsl:copy-of select="$numofResps" /></xsl:attribute>
</xsl:template>

	<xsl:template match="ssn/@perf">
  <xsl:attribute name="perf"><xsl:value-of select="$xxx"/></xsl:attribute>
</xsl:template>

<xsl:template match="v">
<xsl:copy-of select="." />
<a><xsl:value-of select="$_minrep"/></a>
</xsl:template>

<xsl:template name="Calc_minrep">
	<xsl:variable name="numofResps"><xsl:value-of select="count(ssn/p[@isDel='N'])"/></xsl:variable>
	<xsl:value-of select="concat('ass ', 'ssn/@MinPart_S')"/>
</xsl:template>

</xsl:stylesheet>
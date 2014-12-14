<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="node()|@*">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>
<!-- -->

<xsl:variable name="xxx">FUCK</xsl:variable>
<xsl:variable name="numofResps"><xsl:value-of select="count(ssn/p[@isDel='N'])"/></xsl:variable>
<xsl:variable name="MinPart_S"><xsl:value-of select="ssn/@MinPart_S"/></xsl:variable>

<xsl:variable name="_minrep">
	<xsl:call-template name="Calc_minrep">
        <xsl:with-param name="myNode" select="makeRespLs00"/>        
    </xsl:call-template>
</xsl:variable>

<xsl:variable name="makeVs00">
	123123
</xsl:variable>

	<xsl:template match="ssn/@minrep">
  <xsl:attribute name="minrep"><xsl:value-of select="$numofResps" /></xsl:attribute>
</xsl:template>






	<xsl:template match="ssn/@perf">
  <xsl:attribute name="perf"><xsl:value-of select="$xxx"/></xsl:attribute>
</xsl:template>






<xsl:template match="v111">
<xsl:copy-of select="." />
<a><xsl:value-of select="$_minrep"/></a>
</xsl:template>


<xsl:template name="Calc_minrep">
	<xsl:variable name="numofResps"><xsl:value-of select="count(ssn/p[@isDel='N'])"/></xsl:variable>
	<xsl:variable name="nnn"><xsl:value-of select="count(ssn/p[@isDel='N'])"/></xsl:variable>
	
	<xsl:value-of select="floor(($numofResps * 3) div 4)"/> 
	<!--
	$<xsl:value-of select="format-number(//Applications/AveAnnualVolume div 12,'###,###,##0.00')"/> 
	<xsl:value-of select="concat('ass ', 'ssn/@MinPart_S')"/>
	-
	-->
	
	<xsl:value-of select="makeVs00"/> 
</xsl:template>

<xsl:template name="MarkQuestion">

0o00o

    <xsl:for-each select="/ssn/p[@idx='2']">
    	HHHHHHHHHH
        <xsl:attribute name="isDel">
        	<xsl:value-of select="WTF"/>
        </xsl:attribute>
        ZZZZZ
        <xsl:copy-of select="."/>
    </xsl:for-each>

	<xsl:variable name="numofResps"><xsl:value-of select="count(ssn/p[@isDel='N'])"/></xsl:variable>
	<xsl:variable name="nnn"><xsl:value-of select="count(ssn/p[@isDel='N'])"/></xsl:variable>
	
	<xsl:value-of select="floor(($numofResps * 3) div 4)"/> 
	<!--
	$<xsl:value-of select="format-number(//Applications/AveAnnualVolume div 12,'###,###,##0.00')"/> 
	<xsl:value-of select="concat('ass ', 'ssn/@MinPart_S')"/>
	-
	-->

	---------
	<xsl:value-of select="makeVs00"/> 
</xsl:template>

</xsl:stylesheet>